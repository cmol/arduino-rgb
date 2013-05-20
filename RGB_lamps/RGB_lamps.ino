#include <RGBLamp.h>

/*
  RGBLamp.h - Library for controlling RGB diodes.
  Created by Claus Lensbøl, May 19, 2013.
  For license, see LICENSE file.
*/

RGBLamp lamps[4];

void setup() {
  // use a for loop to initialize each pin as an output:
  for (int pin = 2; pin < 14; pin++)  {
    pinMode(pin, OUTPUT);
  }
  
  lamps[0].create(2,3,4);
  lamps[1].create(5,6,7);
  lamps[2].create(8,9,10);
  lamps[3].create(11,12,13);

  // Sets all lamps to a random color
  for (int lamp = 0; lamp < 4; lamp++) {
    int col[] = {random(0, 255),random(0, 255),random(0, 255)};
    lamps[lamp].setColor(col);
  }
  
  // Sleeps for 2 seconds to test the output before moving on
  delay(2000);
}

// This will carry out the fades and so on. These must be run each loop! (!!!)
void work() {
  boolean finish = true;
  
  for (int lamp = 0; lamp < 4; lamp++) {
    if(lamps[lamp].work()) {
      finish = false;
    }
  }
  
  if(finish) {
    // Sets all lamps to fade to a random color
    for (int lamp = 0; lamp < 4; lamp++) {
      int col[] = {random(0, 255),random(0, 255),random(0, 255)};
      lamps[lamp].fade(4000, col);
    }
  }
}

// This is our main loop
void loop() {
  
  // This is where the fun begins
  work();
  
} 
