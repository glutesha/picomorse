#include "morse_key.h"
#include <Arduino.h>

MorseKey::MorseKey(int mode, bool caps, bool rus, bool boot, int button, unsigned long debounce, int chmode, int lang, int capsBtn, int buzz, unsigned long dotDur, int tone, int lineNum, int spaceDur, int wordSpaceDur)
    : morseToLatin({
        {".-",     "a"}, {"-...",   "b"}, {"-.-.",   "c"}, {"-..",    "d"}, {".",      "e"},
        {"..-.",   "f"}, {"--.",    "g"}, {"....",   "h"}, {"..",     "i"}, {".---",   "j"},
        {"-.-",    "k"}, {".-..",   "l"}, {"--",     "m"}, {"-.",     "n"}, {"---",    "o"},
        {".--.",   "p"}, {"--.-",   "q"}, {".-.",    "r"}, {"...",    "s"}, {"-",      "t"},
        {"..-",    "u"}, {"...-",   "v"}, {".--",    "w"}, {"-..-",   "x"}, {"-.--",   "y"},
        {"--..",   "z"}, {"-----",  "0"}, {".----",  "1"}, {"..---",  "2"}, {"...--",  "3"},
        {"....-",  "4"}, {".....",  "5"}, {"-....",  "6"}, {"--...",  "7"}, {"---..",  "8"}, {"----.",  "9"}
      }),
      morseToRussian({
        {".-",     "f"} /*а*/, {"-...",   ","} /*б*/, {".--",    "d"} /*в*/, {"--.",    "u"} /*г*/, {"-..",    "l"} /*д*/,
        {".",      "t"} /*е*/, {"...-",   ";"} /*ж*/, {"--..",   "p"} /*з*/, {"..",     "b"} /*и*/, {".---",   "q"} /*й*/,
        {"-.-",    "r"} /*к*/, {".-..",   "k"} /*л*/, {"--",     "v"} /*м*/, {"-.",     "y"} /*н*/, {"---",    "j"} /*о*/,
        {".--.",   "g"} /*п*/, {".-.",    "h"} /*р*/, {"...",    "c"} /*с*/, {"-",      "n"} /*т*/, {"..-",    "e"} /*у*/,
        {"..-.",   "a"} /*ф*/, {"....",   "["} /*х*/, {"-.-.",   "w"} /*ц*/, {"---.",   "x"} /*ч*/, {"----",   "i"} /*ш*/,
        {"--.-",   "o"} /*щ*/, {"--.--",  "]"} /*ъ*/, {"-.--",   "s"} /*ы*/, {"-..-",   "m"} /*ь*/, {"..-..",  "\'"} /*э*/,
        {"..--",   "."} /*ю*/, {".-.-",   "z"} /*я*/, {"-----",  "0"}, {".----",  "1"}, {"..---",  "2"},
        {"...--",  "3"}, {"....-",  "4"}, {".....",  "5"}, {"-....",  "6"}, {"--...",  "7"},
        {"---..",  "8"}, {"----.",  "9"}
      }),
      last_word(""),
      last_millis(millis()),
      last_space_millis(0),
      dot(dotDur),
      space(spaceDur),
      word_space(wordSpaceDur),
      line(lineNum),
      buzzer_tone(tone),
      key(button),
      button_select_mode_pin(chmode),
      button_language_mode_pin(lang),
      button_capslock_pin(capsBtn),
      buzzer_pin(buzz),
      mode(mode),
      lastPressed(false),
      rus(rus),
      caps(caps),
      bootsel_as_button(boot),
      key_debounce(key, debounce)
{
    pinMode(key, INPUT_PULLUP);
    pinMode(buzzer_pin, OUTPUT);
}

void MorseKey::morse(const bool pressed) {
    const unsigned long current = millis();

    if (!pressed) {
        if (lastPressed) {
            if (current - last_millis >= dot * line) {
                Keyboard.printf("-");
            }
            else if (current - last_millis >= dot) {
                if(rus) {
                    Keyboard.printf("/");
                }
                else{
                    Keyboard.printf(".");
                }
            }
        }
        last_millis = current;
    }
    else{
        if(!lastPressed) {
            if (millis() - last_space_millis >= dot * word_space) {
                if(rus){
                    Keyboard.printf(" | ");
                }
                else{
                    Keyboard.printf(" / ");
                }
            }
            else if (millis() - last_space_millis >= dot * space) {
                Keyboard.printf(" ");
            }
            last_space_millis = current;
        }
    }
}

void MorseKey::decode(const bool pressed) {
    const unsigned long current = millis();
    if (!pressed) {
        if (lastPressed) {
            if (current - last_millis >= dot * line) {
                last_word += "-";
            }
            else if (current - last_millis >= dot) {
                last_word += ".";
            }
        }
        else {
            if (last_word != "") {
                if (millis() - last_space_millis >= dot * space) {
                    const String numbers = "0123456789";
                    if (rus) {
                        if ((numbers.indexOf(morseToRussian[last_word])) != -1 or (!caps)) {
                            Keyboard.printf(morseToRussian[last_word].c_str());
                        }
                        else {
                            Keyboard.press(KEY_LEFT_SHIFT);
                            Keyboard.printf(morseToRussian[last_word].c_str());
                            Keyboard.release(KEY_LEFT_SHIFT);
                        }
                    }
                    else {
                        String key = morseToLatin[last_word];
                        if(caps){
                            key.toUpperCase();
                        }
                        Keyboard.printf(key.c_str());
                    }
                    last_word = "";
                }
            }
        }
        last_millis = current;
    }
    else{
        if(!lastPressed) {
            if (millis() - last_space_millis >= dot * word_space) {
                Keyboard.printf(" ");
            }
            last_space_millis = current;
        }
    }
}
void MorseKey::operate() {
    bool pressed = (bootsel_as_button and BOOTSEL) or key_debounce.read();
    
    bool switched = false;

    if (pressed && !lastPressed) {
        if (mode == 0) {
            Mouse.press(MOUSE_LEFT);
        }
        analogWrite(buzzer_pin, buzzer_tone);
    }
    else if (!pressed && lastPressed) {
        if (mode == 0) {
            Mouse.release(MOUSE_LEFT);
        }
        analogWrite(buzzer_pin, 0);
    }

    if(digitalRead(button_select_mode_pin)){
        mode++;
        mode = mode % 3;
        switched = true;
    }

    if(digitalRead(button_capslock_pin)){
        caps = !caps;
        switched = true;
    }

    if(digitalRead(button_language_mode_pin)){
        rus = !rus;
        switched = true;
    }

    if(switched){
        for(int i = 0; i < 2; i++){
            analogWrite(buzzer_pin, buzzer_tone);
            delay(100);
            analogWrite(buzzer_pin, 0);
            delay(100);
        }
    }

    switch (mode) {
        case 1: {
            morse(pressed);
            break;
        }
        case 2: {
            decode(pressed);
            break;
        }
    }

    lastPressed = pressed;
}