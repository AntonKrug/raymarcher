//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "Color.h"


Color::Color(float init): r(init), g(init), b(init) {
}


Color::Color(float rInit, float gInit, float bInit): r(rInit), g(gInit), b(bInit) {
}


Color Color::operator+(Color second) {
  return Color(r + second.r, g + second.g, b + second.b);
}


void Color::operator+=(Color second) {
  r += second.r;
  g += second.g;
  b += second.b;
  cumulativeAdditionsCount++;
}


Color Color::operator*(float scalar) {
  return Color(r * scalar, g * scalar, b * scalar);
}


Color Color::multiply(float scalar) {
  r *= scalar;
  g *= scalar;
  b *= scalar;

  return *this;
}


Uint32 Color::toNormalizedARGB888() {
  return 255 << 24 | (Uint32(r * 255) << 16) | (Uint32(g * 255) << 8) | (Uint32(b * 255) << 0);
}
