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
void ComplementaryColors::SetColor(int color[]) {
  for (int i = 0; i < 3; i++) {
    _rgb_colors[0][i] = color[i];
  }
}

// Return calculated colors
void ComplementaryColors::GetColors(int colors[][3]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      colors[i][j] = _rgb_colors[i][j];
    }
  }
}

// Calculate tetrads
void ComplementaryColors::Tetrads() {

  double col[][3] = {{_rgb_colors[0][0], _rgb_colors[0][1],_rgb_colors[0][2]},
                     {_rgb_colors[0][0], _rgb_colors[0][1],_rgb_colors[0][2]},
                     {_rgb_colors[0][0], _rgb_colors[0][1],_rgb_colors[0][2]}};

  int shift[] = {150,180,330};
  for(int i = 0; i < 3; i++) {
    _rgb2hsv(col[i]);
    _HueShift(col[i], shift[i]);
    _hsv2rgb(col[i]);
    for(int j = 0; j < 3; j++) {
      _rgb_colors[i+1][j] = (int)col[i][j];
    }
  }

}

void ComplementaryColors::_rgb2hsv(double color[]) {
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

void ComplementaryColors::_hsv2rgb(double color[]) {
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

    i = ((int) h) / 60;
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

void ComplementaryColors::_HueShift(double color[], int degree) {
  color[0] = color[0] + degree;
  color[0] = (color[0] > 360) ? color[0] - 360 : color[0];
}
