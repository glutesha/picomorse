#pragma once
#include <USBMouseKeyboard.h>

class MorseKey {
    unsigned long last_millis;
    unsigned long last_space_millis;
    unsigned long dot;
    int buzzer_tone;
    int key;
    int button_select_mode_pin;
    int button_language_mode_pin;
    int button_capslock_pin;
    int buzzer_pin;
    int mode;
    bool lastPressed;
    bool rus;

    void morse(bool, USBMouseKeyboard&);
    void decode(bool, USBMouseKeyboard&);
    void changeMode(int);

    public:
        MorseKey(int, int, int, int, int, unsigned long, int);
        void operate(USBMouseKeyboard&);
};