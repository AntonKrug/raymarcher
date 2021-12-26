//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_COLOR_H
#define RAYMARCHER_COLOR_H

#include <SDL2/SDL_stdinc.h>
#include <cfloat>

struct Color {
  float r, g, b;
  int cumulativeAdditionsCount = 0;

  explicit Color(float init = 0.0f);
  Color(float rInit, float gInit, float bInit = 0.0f);

  Color operator+(Color second);
  void operator+=(Color second);
  Color operator*(float scalar);

  Color multiply(float scalar);

  Uint32 toNormalizedARGB888();
};


#endif //RAYMARCHER_COLOR_H
