/*
  ComplementaryColors.cpp - Library for calculating complementary colors.
  Created by Claus Lensbøl, Aug 1, 2013.
  For license, see LICENSE file.
*/
#include "Arduino.h"
#include "ComplementaryColors.h"

// Constructor - Does nothing for now (but is needed)
ComplementaryColors::ComplementaryColors() {}

// Get primary color to calculate from
void SetColor(int color[]) {
  for (i = 0; i < 3; i++) {
    _rgb_colors[0][i] = color[i];
  }
}

// Return calculated colors
void GetColors(int colors[][]) {
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      colors[i][j] = _rgb_colors[i][j];
    }
  }
}

// Calculate tetrads
// TODO: Make this based on 2-dimentional arrays.
void Tetrads() {

  double col1 = {_rgb_colors[0][0], _rgb_colors[0][1],_rgb_colors[0][2]};
  double col2 = {_rgb_colors[0][0], _rgb_colors[0][1],_rgb_colors[0][2]};
  double col3 = {_rgb_colors[0][0], _rgb_colors[0][1],_rgb_colors[0][2]};
  _rgb2hsv(col1);
  _rgb2hsv(col2);
  _rgb2hsv(col3);
  _HueShift(col1, 150);
  _HueShift(col2, 180);
  _HueShift(col3, 330);
  _hsv2rgb(col1);
  _hsv2rgb(col2);
  _hsv2rgb(col3);

  _rgb_colors[1][0] = col1[0];
  _rgb_colors[1][1] = col1[1];
  _rgb_colors[1][2] = col1[2];
  _rgb_colors[2][0] = col2[0];
  _rgb_colors[2][1] = col2[1];
  _rgb_colors[2][2] = col2[2];
  _rgb_colors[3][0] = col3[0];
  _rgb_colors[3][1] = col3[1];
  _rgb_colors[3][2] = col3[2];
  _rgb_colors[4][0] = col4[0];
  _rgb_colors[4][1] = col4[1];
  _rgb_colors[4][2] = col4[2];
}

void _rgb2hsv(double color[]) {
  double r = color[0] / 255.0;
  double g = color[1] / 255.0;
  double b = color[2] / 255.0;

  double min = min(r, min(g, b));
  double max = max(r, max(g, b));

  if (min == max) {
    color[0] = 0;
    color[1] = 0;
    color[2] = min;
  }
  else {
    double d = (r==min) ? g-b : ((b==min) ? r-g : b-r);
    double h = (r==min) ? 3.0 : ((b==min) ? 1.0 : 5.0);
    color[0] = 60.0*(h - d / (max - min));
    color[1] = (max - min) / max;
    color[2] = max;
  }
}

void _hsv2rgb(double color[]) {
  double h = color[0];
  double s = color[1];
  double v = color[2];
  double f,n,m,k;
  int i;
  // If we are in greys
  if (s == 0) {
    color[0] = 255.0 * v;
    color[1] = 255.0 * v;
    color[2] = 255.0 * v;
  }
  // If we are not in greys
  else {

    // Quick fix to make sure the switch doesn't break.
    // TODO: Don't quick fix
    if (h == 360) {
      h = 359.0;
    }

    i = (int) h;
    f = h - i;

    m = v * (1 - s);
    n = v * (1 - s * f);
    k = v * (1 - s * (1 - f));

    // The big table that I really don't get.
    if (i == 0) { color[0] = v; color[1] = k; color[2] = m; }
    if (i == 1) { color[0] = n; color[1] = v; color[2] = m; }
    if (i == 2) { color[0] = m; color[1] = v; color[2] = k; }
    if (i == 3) { color[0] = m; color[1] = n; color[2] = v; }
    if (i == 4) { color[0] = k; color[1] = m; color[2] = v; }
    if (i == 5) { color[0] = v; color[1] = m; color[2] = n; }

    // Multiply the colors by 255 to get the RGB representation
    color[0] = color[0] * 255;
    color[1] = color[1] * 255;
    color[2] = color[2] * 255;
  }
}

void _HueShift(double color[], int degree) {
  color[0] = color[0] + degree;
  color[0] = (color[0] > 360) ? color[0] - 360 : color[0];
}
