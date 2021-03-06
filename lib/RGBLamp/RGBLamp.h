/*
  RGBLamp.h - Library for controlling RGB diodes.
  Created by Claus Lensbøl, May 19, 2013.
  For license, see LICENSE file.
*/
#ifndef RGBLamp_h
#define RGBLamp_h
#include "Arduino.h"

class RGBLamp
{
  public:
    RGBLamp();
    void create(int pin_r, int pin_g, int pin_b);
    void fade(unsigned int fade_length, int fade_to[3]);
    bool fade();
    void fadeStop();
    void on();
    void off();
    bool work();
    void setColor(int color[3]);
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
