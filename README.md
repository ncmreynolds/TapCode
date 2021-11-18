# Tap Code
An Arduino library to interpret '[tap code](https://en.wikipedia.org/wiki/Tap_code)' sent with a single button. Tap code is similar to Morse code but easier to send, learn and read while being slower.

It uses a single button and stores the tapped code as a C string for comparison/printing. This library is mostly an enabling one for other projects such as the [LARP hackable RFID lock](https://github.com/ncmreynolds/LarpHackableRfidLock) prop, it's a pretty rubbish input method.

To debounce the button, it uses the [EasyButton](https://easybtn.earias.me/) library.
