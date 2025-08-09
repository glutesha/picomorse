# Picomorse ![stats](https://hackatime-badge.hackclub.com/U091LS2TL8M/picomorse)
Picomorse is an RP2040-based Morse code keyboard. You can make it out of any existing Morse key or a simple tactile button.
Supports English and Russian Morse.
## Build
To build this project in its full configuration, you need:
- Raspberry Pi Pico
- 3-volt buzzer (with an optional resistor)
- 3 Sensor buttons
- Old telegraph key

I've built mine using all the parts listed below, but you can run this project simply by clicking the BOOT button on the board itself. How cool is that?
To upload the firmware, you need PlatformIO CLI or plugin installed. Use the regular PlatformIO upload button or type in ```pio run --target upload``` in your terminal.
## Configuration
You can remap everything in ```defines.h``` file.
## Usage
This project has 3 modes. Use the ```BUTTON_MODE_PIN``` button to switch between them.
### Mouse clicks
Key press = mouse click.
### Dots and lines
Prints out the Morse code. Auto detects spaces between characters and words.
### Decoder
Decode Morse and type out actual letters on your PC. Useful when combined with a keyboard typing test. 
Use the ```BUTTON_CAPS_PIN``` to switch between upper/lower case letters, and the ```BUTTON_LANGUAGE_PIN``` to switch between languages.       
## Technologies
The whole project is written entirely in C++ and the Arduino framework.
