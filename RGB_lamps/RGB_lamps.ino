#include <RGBLamp.h>

RGBLamp lamps[] = {{2,3,4},{5,6,7},{8,9,10},{11,12,13}};

/*RGBLamp lamps[4];
lamps[0]=RGBLamp(2,3,4);
lamps[1]=RGBLamp(5,6,7);
lamps[2]=RGBLamp(8,9,10);
lamps[3]=RGBLamp(11,12,13);

RGBLamp lamps[0](2,3,4);
RGBLamp lamps[1](5,6,7);
RGBLamp lamps[2](8,9,10);
RGBLamp lamps[3](11,12,13);*/


void setup() {
  // use a for loop to initialize each pin as an output:
  for (int pin = 2; pin < 14; pin++)  {
    pinMode(pin, OUTPUT);
  }

  //RGBLamp lamps[] = {{2,3,4},{5,6,7},{8,9,10},{11,12,13}};
  
  // Sets all lamps to a random color
  for (int lamp = 0; lamp < 4; lamp++) {
    lamps[lamp].setColor({random(0, 255),random(0, 255),random(0, 255)});
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
      lamps[lamp].fade(4000, {random(0, 255),random(0, 255),random(0, 255)});
    }
  }
}

// This is our main loop
void loop() {
  
  // This is where the fun begins
  work();
  
} 
