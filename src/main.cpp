#include <Arduino.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"
#include "USBMouse.h"

USBKeyboard keyboard;
USBMouse mouse;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(28, OUTPUT);
}

void loop() {
  if(!digitalRead(2)){
    mouse.press(MOUSE_LEFT);
    Serial.println("PRESS");
  }
  else{
    mouse.release(MOUSE_LEFT);
  }
}
