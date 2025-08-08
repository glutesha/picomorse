#include "morse_key.h"
#include "Arduino.h"

MorseKey::MorseKey(int button, int chmode, int lang, int caps, int buzz, unsigned long dot, int tone, int line, int space, int word_space):
key(button),
button_select_mode_pin(chmode),
button_language_mode_pin(lang),
button_capslock_pin(caps),
buzzer_pin(buzz),
dot(dot),
last_millis(millis()),
buzzer_tone(tone),
rus(true),
mode(2),
line(line),
space(space),
word_space(word_space),
last_space_millis(0),
lastPressed(false),
last_word(""),
morseToLatin({
        {".-",     "A"},
        {"-...",   "B"},
        {"-.-.",   "C"},
        {"-..",    "D"},
        {".",      "E"},
        {"..-.",   "F"},
        {"--.",    "G"},
        {"....",   "H"},
        {"..",     "I"},
        {".---",   "J"},
        {"-.-",    "K"},
        {".-..",   "L"},
        {"--",     "M"},
        {"-.",     "N"},
        {"---",    "O"},
        {".--.",   "P"},
        {"--.-",   "Q"},
        {".-.",    "R"},
        {"...",    "S"},
        {"-",      "T"},
        {"..-",    "U"},
        {"...-",   "V"},
        {".--",    "W"},
        {"-..-",   "X"},
        {"-.--",   "Y"},
        {"--..",   "Z"},
        {"-----",  "0"},
        {".----",  "1"},
        {"..---",  "2"},
        {"...--",  "3"},
        {"....-",  "4"},
        {".....",  "5"},
        {"-....",  "6"},
        {"--...",  "7"},
        {"---..",  "8"},
        {"----.",  "9"},}),
morseToRussian({
        {".-",     'f'},  // А
        {"-...",   ','},  // Б
        {".--",    'd'},  // В
        {"--.",    'u'},  // Г
        {"-..",    'l'},  // Д
        {".",      't'},  // Е
        {"...-",   ';'},  // Ж
        {"--..",   'p'},  // З
        {"..",     'b'},  // И
        {".---",   'q'},  // Й
        {"-.-",    'r'},  // К
        {".-..",   'k'},  // Л
        {"--",     'v'},  // М
        {"-.",     'y'},  // Н
        {"---",    'j'},  // О
        {".--.",   'g'},  // П
        {".-.",    'h'},  // Р
        {"...",    'c'},  // С
        {"-",      'n'},  // Т
        {"..-",    'e'},  // У
        {"..-.",   'a'},  // Ф
        {"....",   '['},  // Х
        {"-.-.",   'w'},  // Ц
        {"---.",   'x'},  // Ч
        {"----",   'i'},  // Ш
        {"--.-",   'o'},  // Щ
        {"--.--",  ']'},  // Ъ
        {"-.--",   's'},  // Ы
        {"-..-",   'm'},  // Ь
        {"..-..",  '\''}, // Э
        {"..--",   '.'},  // Ю
        {".-.-",   'z'},  // Я
        {"-----",  '0'},
        {".----",  '1'},
        {"..---",  '2'},
        {"...--",  '3'},
        {"....-",  '4'},
        {".....",  '5'},
        {"-....",  '6'},
        {"--...",  '7'},
        {"---..",  '8'},
        {"----.",  '9'},})
{
    pinMode(key, INPUT_PULLUP);
    pinMode(buzzer_pin, OUTPUT);
}

void MorseKey::morse(const bool pressed, USBMouseKeyboard &keyboard) {
    const unsigned long current = millis();

    if (!pressed) {
        if (lastPressed) {
            if (millis() - last_space_millis >= dot * word_space) {
                keyboard.printf(" / ");
            }
            else if (millis() - last_space_millis >= dot * space) {
                keyboard.printf(" ");
            }
            if (current - last_millis >= dot * line) {
                keyboard.printf("-");
            }
            else if (current - last_millis >= dot) {
                keyboard.printf(".");
            }
            last_space_millis = current;
        }
        last_millis = current;
    }
}

void MorseKey::decode(const bool pressed, USBMouseKeyboard &keyboard) {
    const unsigned long current = millis();
    if (!pressed) {
        if (lastPressed) {
            if (millis() - last_space_millis >= dot * word_space) {
                keyboard.printf(" ");
                last_word = "";
            }
            if (current - last_millis >= dot * line) {
                last_word += "-";
            }
            else if (current - last_millis >= dot) {
                last_word += ".";
            }
            last_space_millis = current;
        }
        else {
            if (last_word != "") {
                if (millis() - last_space_millis >= dot * space) {
                    const String numbers = "0123456789";
                    if (rus) {
                        if (numbers.indexOf(String(morseToRussian[last_word])) != -1) {
                            keyboard.key_code(morseToRussian[last_word]);
                        }
                        else {
                            keyboard.key_code(morseToRussian[last_word], KEY_SHIFT);
                        }
                    }
                    else {
                        keyboard.printf("%s", morseToLatin[last_word].c_str());
                    }
                    last_word = "";
                }
            }
        }
        last_millis = current;
    }
}
void MorseKey::operate(USBMouseKeyboard& device) {
    bool pressed = !digitalRead(key);

    if (pressed && !lastPressed) {
        if (mode == 0) {
            device.press(MOUSE_LEFT);
        }
        analogWrite(buzzer_pin, buzzer_tone);
    }
    else if (!pressed && lastPressed) {
        if (mode == 0) {
            device.release(MOUSE_LEFT);
        }
        analogWrite(buzzer_pin, 0);
    }

    switch (mode) {
        case 1: {
            morse(pressed, device);
            break;
        }
        case 2: {
            decode(pressed, device);
            break;
        }
    }

    lastPressed = pressed;
}