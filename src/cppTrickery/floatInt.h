//
// Created by anton.krug@gmail.com on 29/12/21.
// License: MIT
//

#ifndef RAYMARCHER_FLOATINT_H
#define RAYMARCHER_FLOATINT_H

#include <cstdint>

template <int thousands>
struct floatInt {
  constexpr static float value = thousands / 1000.0f;
};


#endif //RAYMARCHER_FLOATINT_H
