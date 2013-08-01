/*
  ComplemetaryColors.h - Library for calculating complemetary colors.
  Created by Claus Lensbøl, Aug 1, 2013.
  For license, see LICENSE file.
*/
#ifndef ComplementaryColors_h
#define ComplementaryColors_h
#include "Arduino.h"

class ComplementaryColors
{
  public:
    ComplementaryColors();
    void SetColor(int color[]);
    void GetColors(int colors[][]);
    void Tetrads();
  private:
    int  _rgb_colors[4][3];
    void _rgb2hsv(double color[]);
    void _hsv2rgb(double color[]);
    void _HueShift(double color[], int degree);
};

#endif
