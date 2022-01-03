//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_COLOR_H
#define RAYMARCHER_COLOR_H

#include <SDL2/SDL_stdinc.h>
#include <cfloat>

#include "config.h"


struct color {
  float r, g, b;

  static constexpr float sampleNormalizer    = 1.0f   / config::maxSamples;
  static constexpr float sampleNormalizer255 = 255.0f / config::maxSamples;

  explicit color(float init = 0.0f);
  color(float rInit, float gInit, float bInit = 0.0f);

  color operator+(color second);
  void operator+=(color second);
  color operator*(float scalar);

  color multiply(float scalar);
  color clamp();

  Uint32 toNormalizedARGB888();
  Uint32 hdrToNormalizedLdrARGB8888();
};


#endif //RAYMARCHER_COLOR_H
