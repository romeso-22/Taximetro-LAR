/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by ELECTRONOOBS, oct 14, 2016.
 */

#include <Wtv020sd16p.h>

int resetPin = 4;  // The pin number of the reset pin.
int clockPin = 5;  // The pin number of the clock pin.
int dataPin = 6;  // The pin number of the data pin.
int busyPin = 7;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

void setup() {
  //Initializes the module.
  wtv020sd16p.reset();
  Serial.begin(9600);
}

void loop() {
  
 
  

wtv020sd16p.playVoice(i);



}


