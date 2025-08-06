#include <Arduino.h>
#include "FastLED.h"

#include "PluggableUSBHID.h"
#include "USBMouse.h"

USBMouse mouse;

CRGB leds[1];

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, 16>(leds, 1);
}
 
void loop() {
  if(!digitalRead(2)){
    mouse.press(MOUSE_LEFT);
    tone(28, 1000, 8);
    Serial.println("PRESS");
    leds[0] = CRGB::Blue;
  }
  else{
    leds[0] = CRGB::Black;
    noTone(28);
    mouse.release(MOUSE_LEFT);
  }
  FastLED.show(); 
}
