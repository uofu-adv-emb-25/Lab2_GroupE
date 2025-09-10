# Manual Test Plan
The code does two things: blink the LED, and interact with serial data.

## Setting up the test scenario
1. Plug in the PI Pico into a USB port
2. Execute the following commands from the root of the repository to build and flash the code:
    - `cmake -B build -S .`
    - `cmake --build build`
    - `picotool load -f build/src/hello_freertos.elf`
3. Unplug and replug the Pico

## Exercising the System
### Testing the LED
1. Observe the LED blinking. Every 5th blink, the LED stays off slightly longer
2. After one longer off cycle, count the number of times the LED turns on before the next longer off cycle

### Testing the Serial Behavior
1. Open the serial monitor in the bottom of VSCode
2. Select the following settings:
    - Monitor Mode: Serial
    - View Mode: Text
    - Port: /dec/ttyACM0 - Raspberry Pi (Or similar)
    - Baud rate: 115200
3. Send the following messages one at a time over the serial port:
    - A
    - a
    - Z
    - z
    - AZazAZaz
    - <>[]
    - p[];Lk

## Expected Behavior
### LED Behavior 
The LED blinks at 1 hZ (500 mS on and 500 mS off). After 5 blinks, the LED stays off for an extra 500mS (1 sec total).

### Serial Behavior
After each sent message, the Pico responds with a message.
The user received message should have uppercase letters replaced with lowercase letters and lowercase letters replaced with uppercase letters. All other characters are unchanged.

The above messages should have resulted in the below responses:
    - a
    - A
    - z
    - Z
    - azAZazAZ
    - <>[]
    - P[];lK