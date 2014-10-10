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
float cycleFade[4] = {0,0,0,0};

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

  setColors();

  for (int lamp = 0; lamp < 4; lamp++) {
    lamps[lamp].fade(2000, dayCols[10]);
  }
}

// This will carry out the fades and so on. These must be run each loop! (!!!)
void work() {
  boolean finish = true;

  for (int lamp = 0; lamp < 4; lamp++) {
    if(lamps[lamp].work()) {
      finish = false;
    }
  }

  // Autonomus mode
  // Check if lamps are supposed to fade
  for (int lamp = 0; lamp < 4; lamp++) {
    if (cycleFade[lamp] != 0) {
      if (!lamps[lamp].fade()) {
        lamps[lamp].fade(cycleFade[lamp], colors[random(0, 215)]);
      }
    }
  }

}

// We need to be able to stop the fading
void unset(int lamp) {
  cycleFade[lamp] = 0;
  lamps[lamp].fadeStop();
}

void controller() {
  // Read control data from the serial port to decide what to do with the lamps
  if(Serial.available() > 0) {

    // Setup variables for control
    unsigned char ctrl = Serial.read();
    int selected_lamp = 5; // As 4 should be the higest needed value.
    int r,g,b;

    // Lamp select
    selected_lamp = (ctrl & 224) >> 5;

    // Mode select
    ctrl = ctrl & 31; // Remove the selector bits

    if (ctrl == 0) {
      // Set color for lamp(s)
      //Serial.println("Set Color");
      char cols[3];
      Serial.readBytes(cols,3);

      int col[] = {cols[0],cols[1],cols[2]};
      for(int i = 0; i < 3; i++) {
        col[i] = col[i] < 0 ? col[i] + 256 : col[i];
      }
      if (selected_lamp < 4) {
        unset(selected_lamp);
        lamps[selected_lamp].setColor(col);
      }
      else {
        for(int lamp = 0; lamp < 4; lamp++) {
          unset(lamp);
          lamps[lamp].setColor(col);
        }
      }
    }
    else if (ctrl == 1) {
      //Fade to color for lamp(s)
      char cols[4];
      Serial.readBytes(cols,4);
      int col[] = {cols[0],cols[1],cols[2]};
      for(int i = 0; i < 3; i++) {
        col[i] = col[i] < 0 ? col[i] + 256 : col[i];
      }
      /*Serial.print("Fade Color:");
      Serial.print(col[0]);
      Serial.print("-");
      Serial.print(col[1]);
      Serial.print("-");
      Serial.println(col[2]);*/
      int fade_time = cols[3];

      if (selected_lamp < 4) {
        unset(selected_lamp);
        lamps[selected_lamp].fade(fade_time*100,col);
      }
      else {
        for(int lamp = 0; lamp < 4; lamp++) {
          unset(lamp);
          lamps[lamp].fade(fade_time*100,col);
        }
      }
    }
    else if (ctrl == 10) {
      //CycleFade for lamp(s)
      char ctime[1];
      Serial.readBytes(ctime,1);
      int time = ctime[0];

      if (selected_lamp < 4) {
        unset(selected_lamp);
        cycleFade[selected_lamp] = time*1000.0;
      }
      else {
        for(int lamp = 0; lamp < 4; lamp++) {
          unset(lamp);
          cycleFade[lamp] = time*1000.0;
        }
      }
    }
    else {
      Serial.println("Ooops");

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
  dayCols[10][1] = 175;
  dayCols[10][2] = 50;

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
  controller();
  work();

}
