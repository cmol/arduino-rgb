#include <ComplementaryColors.h>
#include <RGBLamp.h>

/*
  RGBLamp.h - Library for controlling RGB diodes.
  Created by Claus Lensbøl, May 19, 2013.
  For license, see LICENSE file.
*/

RGBLamp lamps[4];
int colors[216][3];
int dayCols[20][3];

void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(15));
  
  // use a for loop to initialize each pin as an output:
  for (int pin = 2; pin < 14; pin++)  {
    pinMode(pin, OUTPUT);
  }

  lamps[0].create(2,3,4);
  lamps[1].create(5,6,7);
  lamps[2].create(8,9,10);
  lamps[3].create(11,12,13);

  // Sets all lamps to a random color
  /*for (int lamp = 0; lamp < 4; lamp++) {
    int col[] = {random(0, 255),random(0, 255),random(0, 255)};
    lamps[lamp].setColor(col);
    //lamps[lamp].on();
  }*/
  
  // Start at the max of colors to test the board and lamps
  int col0[] = {255,0,0};
  lamps[0].setColor(col0);
  int col1[] = {0,255,0};
  lamps[1].setColor(col1);
  int col2[] = {0,0,255};
  lamps[2].setColor(col2);
  int col3[] = {255,255,255};
  lamps[3].setColor(col3);
  
  delay(2000);
  lamps[0].setColor(col3);
  lamps[1].setColor(col0);
  lamps[2].setColor(col1);
  lamps[3].setColor(col2);
  
  delay(2000);
  lamps[0].setColor(col2);
  lamps[1].setColor(col3);
  lamps[2].setColor(col0);
  lamps[3].setColor(col1);
  
  delay(2000);
  lamps[0].setColor(col1);
  lamps[1].setColor(col2);
  lamps[2].setColor(col3);
  lamps[3].setColor(col0);
  
  // Sleeps for 2 seconds to test the output before moving on
  delay(2000);
  setColors();
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
      lamps[lamp].fade(10000, colors[random(0, 215)]);
    }
  }
}

void setColors() {
  
  // Set up a 216 color array, so that we dont get all whites
  int i = 0;
  for(int r = 0; r <= 255; r += 51) {
    for(int g = 0; g <= 255; g += 51) {
      for(int b = 0; b <= 255; b += 51) {
        colors[i][0] = r;
        colors[i][1] = g;
        colors[i][2] = b;
        i++;
      }
    }
  }
  
  // Trying to simulate the colors of the day
  // Sunset
  dayCols[0][0] = 182;
  dayCols[0][1] = 126;
  dayCols[0][2] = 91;
  
  // Noon
  dayCols[1][0] = 192;
  dayCols[1][1] = 191;
  dayCols[1][2] = 173;
  
  // Clouds, haze
  dayCols[2][0] = 189;
  dayCols[2][1] = 190;
  dayCols[2][2] = 192;
  
  // Overcast
  dayCols[3][0] = 174;
  dayCols[3][1] = 183;
  dayCols[3][2] = 190;
  
  // Midnight blue
  dayCols[4][0] = 0;
  dayCols[4][1] = 51;
  dayCols[4][2] = 102;
  
  // Storm Petrel
  dayCols[5][0] = 0;
  dayCols[5][1] = 24;
  dayCols[5][2] = 72;
  
  // Darkest Blue Violet
  dayCols[6][0] = 48;
  dayCols[6][1] = 24;
  dayCols[6][2] = 96;
  
  // Pansy
  dayCols[7][0] = 72;
  dayCols[7][1] = 48;
  dayCols[7][2] = 120;
  
  // Dusty Violet
  dayCols[8][0] = 96;
  dayCols[8][1] = 72;
  dayCols[8][2] = 120;
  
  // Midnight blue
  dayCols[9][0] = 144;
  dayCols[9][1] = 96;
  dayCols[9][2] = 144;
  
  // Candle
  dayCols[10][0] = 255;
  dayCols[10][1] = 147;
  dayCols[10][2] = 41;
  
  // Tungsten 40W
  dayCols[11][0] = 255;
  dayCols[11][1] = 197;
  dayCols[11][2] = 143;
  
  // Tungsten 100W
  dayCols[12][0] = 255;
  dayCols[12][1] = 214;
  dayCols[12][2] = 170;
  
  // Halogen
  dayCols[13][0] = 255;
  dayCols[13][1] = 241;
  dayCols[13][2] = 224;
  
  // Direct sun
  dayCols[14][0] = 255;
  dayCols[14][1] = 255;
  dayCols[14][2] = 255;
  
  // Evening Sun
  dayCols[15][0] = 227;
  dayCols[15][1] = 111;
  dayCols[15][2] = 30;
  
  // Dusk purple 1
  dayCols[16][0] = 151;
  dayCols[16][1] = 15;
  dayCols[16][2] = 134;
  
  // Dusk purple 2
  dayCols[17][0] = 125;
  dayCols[17][1] = 15;
  dayCols[17][2] = 78;
  
  // Dusk purple 3
  dayCols[18][0] = 125;
  dayCols[18][1] = 12;
  dayCols[18][2] = 100;
  
  // Prussian Blue
  dayCols[19][0] = 0;
  dayCols[19][1] = 49;
  dayCols[19][2] = 83;
  
}

// This is our main loop
void loop() {

  // This is where the fun begins
  work();

}
