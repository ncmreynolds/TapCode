/*
 * Example of using tap code to send text to a device
 * 
 * Debug is enabled to help with typing practice
 * 
 * See https://en.wikipedia.org/wiki/Tap_code for source and licence
 * 
 */

#include <TapCode.h>

TapCode tapInput(2);  //Start a tap input button on pin 2

 void setup() {
  Serial.begin(115200);
  tapInput.debug(Serial); //Enable debugging on Serial
  tapInput.begin();
}

void loop() {
  tapInput.read();  //Check for tap input
  if(tapInput.changed())
  {
    Serial.println(tapInput.word());
  }
}
