# Picomorse
Picomorse is a RP2040 based morse code keyboard. You can make it basically out of any existing morse key or a simple tactile button.
Supports english and russian morse.
## Build
To build this project in its full configuration, you need:
- Raspberry Pi Pico
- 3 volt buzzer (with an optional resistor)
- 3 Sensor buttons
- Old telegraph key

I've built mine using all these parts below, but you can actually run this project just using the board itself by clicking the BOOT button. How cool is that?
## Configuration
You can remap basically everything in ```defines.h``` file.
## Usage
This projects has 3 modes. Use the ```BUTTON_MODE_PIN``` button to switch between them.
### Mouse clicks
Key press = mouse click.
### Dots and lines
Types out the morse code itself. Auto detects spaces between characters and words.
### Decoder
Decode morse and type out actual letters on your PC. Useful when combined with a keyboard typing test. 
Use the ```BUTTON_CAPS_PIN``` to switch between upper/lower case letters, and the ```BUTTON_LANGUAGE_PIN``` to switch between languages.       
## Technologies
The whole project is written entirely in C++ and Arduino framework with no additional libraries. As simple as that.