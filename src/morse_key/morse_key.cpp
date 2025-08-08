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
rus(false),
mode(1),
line(line),
space(space),
word_space(word_space),
last_space_millis(0),
lastPressed(false)
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
    }

    lastPressed = pressed;
}