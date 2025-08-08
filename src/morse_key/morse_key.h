#pragma once
#include <USBMouseKeyboard.h>
#include <map>

class MorseKey {
    std::map<String, String> morseToLatin;
    std::map<String, char> morseToRussian;
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

    void morse(bool, USBMouseKeyboard&);
    void decode(bool, USBMouseKeyboard&);
    void changeMode(int);

    public:
        MorseKey(int, int, int, int, int, unsigned long, int, int, int, int);
        void operate(USBMouseKeyboard&);
};