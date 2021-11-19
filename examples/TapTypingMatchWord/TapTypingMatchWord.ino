/*
 * Example of using tap code to send a 'keyword' and see if it matches
 * 
 * Use matches() instead strcmp, as the library deals with case and the fact C & K are the same
 * 
 * See https://en.wikipedia.org/wiki/Tap_code for source and licence
 * 
 */

#include <TapCode.h>

TapCode tapInput(2);  //Start a tap input button on pin 2

char wordToMatch[] = "Check";

 void setup() {
  Serial.begin(115200);
  tapInput.debug(Serial); //Enable debugging on Serial
  tapInput.begin();
  Serial.print("Try to match the word ");
  Serial.println(wordToMatch);
}

void loop() {
  tapInput.read();  //Check for tap input
  if(tapInput.finished())
  {
    Serial.print("Entered word \"");
    Serial.print(tapInput.word());
    if(tapInput.matches(wordToMatch))
    {
      Serial.println("\" - matches");
    }
    else
    {
      Serial.println("\" - does not match, try again");
    }
    tapInput.reset(); //Reset the word to try again, otherwise it will keep the incorrect try
  }
}
