/*
  RGBLamp.cpp - Library for controlling RGB diodes.
  Created by Claus Lensbøl, May 19, 2013.
  For license, see LICENSE file.
*/
#include "Arduino.h"
#include "RGBLamp.h"

// Constructor - Does nothing for now (but is needed)
RGBLamp::RGBLamp() {}

void RGBLamp::create(int pin_r, int pin_g, int pin_b) {
  _pins[0]    = pin_g;
  _pins[1]    = pin_r;
  _pins[2]    = pin_b;
  _fade_start = 0;
  _fade_end   = 0;
  _fade       = false;
}

// -------- FADES START --------

// Takes fade length in millis, and color to fade to
void RGBLamp::fade(float fade_length, int fade_to[]) {
  _fade_start			= millis();
  _fade_end				= millis() + fade_length;

  for(int i = 0 ; i < 3 ; i++) {
    _fade_from[i] = _current_color[i];
    _fade_to[i]   = fade_to[i];
  }
  _fade           = true;
}

// Stop fading
void RGBLamp::fadeStop() {
  _fade = false;
}

// Does the actual fading
bool RGBLamp::fade() {
  if(_fade) {

    _fade = false;

    // Test to see if we have used to much time on fading and
    // end the fading (set final color and set _fade to false).
    if(millis() >= _fade_end) {
      setColor(_fade_to);
    }
    else {
      int color[] = {0,0,0};

      for(int i = 0; i < 3 ; i++) {
        float now = ((float)millis() - _fade_start);
        float fl = (_fade_end - _fade_start);
        float fromto = (float) (_fade_from[i] - _fade_to[i]);
        int col = (now/fl) * (fromto);
        color[i] = _fade_from[i] - col;

        if (color[i] != _fade_to[i]) {
          _fade = true;
        }
      }

      setColor(color);
    }
  }

  return _fade;
}

// -------- FADES END ----------

void RGBLamp::off() {
  for(int i = 0 ; i < 3 ; i++) {
    digitalWrite(_pins[i], LOW);
  }
}

void RGBLamp::on() {
  for(int i = 0; i < 3 ; i++) {
    digitalWrite(_pins[i], HIGH);
  }
}

void RGBLamp::setColor(int color[]) {
  for(int i = 0; i < 3 ; i++) {
    _current_color[i] = color[i];
    analogWrite(_pins[i], color[i]);
  }
}

// Place things here that needs to be done with all the lamps all the time
bool RGBLamp::work() {
	return fade();
}
