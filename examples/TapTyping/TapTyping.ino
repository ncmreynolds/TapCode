/*
 * Example of using tap code to send text to a device
 * 
 * See https://en.wikipedia.org/wiki/Tap_code for how to use
 * 
 */

#include <TapCode.h>

TapCode tapInput(RX);

uint8_t lastLength = 0;

 void setup() {
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY); //Note SERIAL_TX_ONLY allows use of RX for a button to save pins
  //tapInput.Debug(Serial);
  tapInput.begin();
}

void loop() {
  tapInput.Housekeeping();
  if(tapInput.Length() > lastLength)
  {
    lastLength = tapInput.Length();
    Serial.println(tapInput.Text());
  }
}
