#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "defines.h"
#include "morse_key/morse_key.h"

MorseKey *morse = nullptr;
bool prevPressed = false;

void setup() {
  Serial.begin(SERIAL_MONITOR_BAUDRATE);
  Keyboard.begin();
  Mouse.begin();
  morse = new MorseKey(DEFAULT_MODE, DEFAULT_CAPS, DEFAULT_RUS, BOOTSEL_AS_BUTTON, BUTTON_PIN, DEBOUNCE, BUTTON_MODE_PIN, BUTTON_LANGUAGE_PIN, BUTTON_CAPS_PIN, BUZZER_PIN, DOT, BUZZER_TONE, LINE, SPACE, WORD);
}

void loop() {
  morse->operate();
}