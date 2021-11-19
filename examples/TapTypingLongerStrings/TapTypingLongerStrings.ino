/*
 * Example of using tap code to send text to a device
 * 
 * Pause between words to make them into a longer sentence
 * 
 * Once you've practice a bit, turn debugging off
 * 
 * See https://en.wikipedia.org/wiki/Tap_code for source and licence
 * 
 */

#include <TapCode.h>

TapCode tapInput(2);  //Start a tap input button on pin 2

String sentence;

 void setup() {
  Serial.begin(115200);
  tapInput.debug(Serial); //Enable debugging on Serial
  tapInput.begin();
}

void loop() {
  tapInput.read();  //Check for tap input
  if(tapInput.finished())
  {
    sentence += ' ';
    sentence += String(tapInput.word());
    tapInput.reset(); //Clear the current word
    Serial.println("Sentence: " + sentence);
  }
}
