/*
  RGBLamp.h - Library for controlling RGB diodes.
  Created by Claus Lensbøl, May 19, 2013.
*/
#ifndef RGBLamp_h
#define RGBLamp_h
#include "Arduino.h"

class RGBLamp
{
  public:
    RGBLamp(int pin_r, int pin_g, int pin_b);
    void fade(int fade_length, int fade_to[]);
    void fade();
    void on();
    void off();
    bool work();
    void setColor(int color[]);
  private:
    int           _pins[3];
    int           _current_color[3];
    int           _fade_from[3];
    int           _fade_to[3];
    unsigned long _fade_start;
    unsigned long _fade_end;
    bool _fade;
};

#endif
