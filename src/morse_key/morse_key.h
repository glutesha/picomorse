#pragma once
#include <map>
#include <Keyboard.h>
#include <Mouse.h>
#include "button/button.h"

class MorseKey {
    std::map<String, String> morseToLatin;
    std::map<String, String> morseToRussian;
    String last_word;
    unsigned long last_millis;
    unsigned long last_space_millis;
    unsigned long dot;
    int space;
    int word_space;
    int line;
    int buzzer_tone;
    int key;
    int button_select_mode_pin;
    int button_language_mode_pin;
    int button_capslock_pin;
    int buzzer_pin;
    int mode;
    bool lastPressed;
    bool rus;
    bool caps;
    bool bootsel_as_button;
    Button key_debounce;

    void morse(bool pressed);
    void decode(bool pressed);

    public:
        MorseKey(int mode, bool caps, bool rus, bool boot, int button, unsigned long debounce, int chmode, int lang, int capsBtn, int buzz, unsigned long dotDur, int tone, int lineNum, int spaceDur, int wordSpaceDur);
        void operate();
};