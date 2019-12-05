# Christmas 2018 Lights

This is an Arduino sketch for individually addressable LEDs that can be controlled by rotary encoders.

It uses FastLED, a RotaryEncoder library, and the Timer library. FastLED.show() is called in the timer loop.

I used a Teensy 3.2 for this and still lost signals from the rotary encoders; you need to use a fast board.

# No Rotary?

If you don't want to mess with rotary encoders, the default setting is quite nice.
