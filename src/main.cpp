#include <Arduino.h>
#include <USBMouseKeyboard.h>

#include "defines.h"
#include "morse_key/morse_key.h"

MorseKey *morse = nullptr;
USBMouseKeyboard device;

bool prevPressed = false;

void setup() {
  Serial.begin(SERIAL_MONITOR_BAUDRATE);
  morse = new MorseKey(BUTTON_PIN, BUTTON_MODE_PIN, BUTTON_LANGUAGE_PIN, BUTTON_CAPS_PIN, BUZZER, DOT, BUZZER_TONE, LINE, SPACE, WORD);
}

void loop() {
  morse->operate(device);
}