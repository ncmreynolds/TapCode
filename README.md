# Tap Code
An Arduino library to interpret '[tap code](https://en.wikipedia.org/wiki/Tap_code)' sent with a single button. Tap code is similar to Morse code but easier to send, learn and read while being slower.

It uses a single button and stores the tapped code as a C string for comparison/printing. This library is mostly an enabling one for other projects such as the [LARP hackable RFID lock](https://github.com/ncmreynolds/LarpHackableRfidLock) prop, it's a pretty rubbish input method.

To debounce the button, it uses the [EasyButton](https://easybtn.earias.me/) library.

In order to type you tap the button to pick out the letter at the row and column in this table, pausing slightly between the row and column. There is no letter 'K', 'C' substitutes for 'K'.

|  A   |  B   |  C   |  D   |  E   |
|:----:|:----:|:----:|:----:|:----:|
|  F   |  G   |  H   |  I   |  J   |
|  L   |  M   |  N   |  O   |  P   |
|  Q   |  R   |  S   |  T   |  U   |
|  V   |  W   |  X   |  Y   |  Z   |

So to type 'HELLO' you would do the following taps on the button.

2	3

1	5

3	1

3	1

3	4

If you turn on debugging it will show the row and column selection making it easier for practice.
