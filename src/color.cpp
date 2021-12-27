//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "color.h"
#include "helper.h"


color::color(float init): r(init), g(init), b(init) {
}


color::color(float rInit, float gInit, float bInit): r(rInit), g(gInit), b(bInit) {
}


color color::operator+(color second) {
  return color(r + second.r, g + second.g, b + second.b);
}


void color::operator+=(color second) {
  r += second.r;
  g += second.g;
  b += second.b;
}


color color::operator*(float scalar) {
  return color(r * scalar, g * scalar, b * scalar);
}


color color::multiply(float scalar) {
  r *= scalar;
  g *= scalar;
  b *= scalar;

  return *this;
}


Uint32 color::toNormalizedARGB888() {
  return 255 << 24 | (Uint32(r * 255) << 16) | (Uint32(g * 255) << 8) | (Uint32(b * 255) << 0);
}


color color::clamp() {
  r = helper::clamp(r, 0.0f, 1.0f);
  g = helper::clamp(g, 0.0f, 1.0f);
  b = helper::clamp(b, 0.0f, 1.0f);

  return *this;
}
