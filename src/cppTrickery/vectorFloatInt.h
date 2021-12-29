//
// Created by anton.krug@gmail.com on 29/12/21.
// License: MIT
//

#ifndef RAYMARCHER_VECTORFLOATINT_H
#define RAYMARCHER_VECTORFLOATINT_H

#include "floatInt.h"

template<int xInit, int yInit, int zInit>
struct vectorFloatInt {
  static constexpr float x = floatInt<xInit>::value;
  static constexpr float y = floatInt<yInit>::value;
  static constexpr float z = floatInt<zInit>::value;
};


#endif //RAYMARCHER_VECTORFLOATINT_H
