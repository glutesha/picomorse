#pragma once
#include <Arduino.h>
#include "USBKeyboard.h"
#include "USBMouse.h"

class MorseKey {
    unsigned long last_millis;
    unsigned long line_millis;
    int button_pin;
    int button_select_mode_pin;
    int button_language_mode_pin;
    int button_capslock_pin;
    int buzzer_pin;
    int mode;
    bool rus;

    void clicks(int, int, USBMouse&);
    void morse(int, int, USBKeyboard&);
    void decode(int, int, USBKeyboard&);

    public:
        MorseKey(int, int, USBMouse&, USBKeyboard&);
        void operate();
};