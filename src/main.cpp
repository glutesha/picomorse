#include <Arduino.h>
#include <PluggableUSBHID.h>
#include <USBMouse.h>
#include "FastLED.h"

USBMouse Mouse;
CRGB leds[1];

bool prevPressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  digitalWrite(26, LOW);
  FastLED.addLeds<NEOPIXEL, 16>(leds, 1); 
}

void loop() {
  bool pressed = !digitalRead(2);
  if (pressed && !prevPressed) {
    Mouse.press(MOUSE_LEFT);
    Serial.println("PRESS");
    analogWrite(28, 200);
    leds[0] = CRGB::Blue;
  }
  else if (!pressed && prevPressed) {
    Mouse.release(MOUSE_LEFT);
    leds[0] = CRGB::Black;
    analogWrite(28, 0);
  }
  prevPressed = pressed;
  FastLED.show();
  delay(50);
}