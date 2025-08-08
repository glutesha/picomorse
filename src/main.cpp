#include <Arduino.h>
#include <PluggableUSBHID.h>
#include <USBMouse.h>

#include "defines.h"

USBMouse Mouse;

bool prevPressed = false;

void setup() {
  Serial.begin(SERIAL_MONITOR_BAUDRATE);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  bool pressed = !digitalRead(BUTTON_PIN);
  if (pressed && !prevPressed) {
    Mouse.press(MOUSE_LEFT);
    Serial.println("PRESS");
    analogWrite(BUZZER, 200);
  }
  else if (!pressed && prevPressed) {
    Mouse.release(MOUSE_LEFT);
    analogWrite(BUZZER, 0);
  }
  prevPressed = pressed;
  delay(50);
}