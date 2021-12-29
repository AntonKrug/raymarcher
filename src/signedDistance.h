//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//


#ifndef RAYMARCHER_SIGNEDDISTANCE_H
#define RAYMARCHER_SIGNEDDISTANCE_H

#include "vector.h"
#include "helper.h"
#include "cppTrickery/floatInt.h"

namespace signedDistance {

  float box(vector point, vector size);
  float mhcpLogoCylinder(vector point);

  template<int sizeXint, int sizeYint, bool quadrant1, bool quadrant7, bool quadrant9, bool quadrant3>
  float mhcpDodlyDood(vector point) {
    // Only C++20 stats supporting float as a non-type template parameter, but I want this code to be C++17 compatible
    // so therefore this workaround.
    // https://en.cppreference.com/w/cpp/language/template_parameters#Non-type_template_parameter
    constexpr float sizeX = floatInt<sizeXint>::value;
    constexpr float sizeY = floatInt<sizeYint>::value;

    const float  roundNess      = 0.25f; // By default all corners are rounded
    const vector smoothSize     = vector(sizeX - roundNess, sizeY - roundNess, 2.0f);

    const vector sharpSizeHalf  = vector(+sizeX / 2.0f, +sizeY / 2.0f, 2.0f);

    const vector cornerSame     = vector(+sizeX / 2.0f, +sizeY / 2.0f, 0.0f);
    const vector cornerOpposite = vector(+sizeX / 2.0f, -sizeY / 2.0f, 0.0f);

    // First calculating the whole box with smooth rounded courners
    float answer = box(point, smoothSize) - roundNess;

    // Able to make any of the 4 corners/quadrants sharp, the numbers are based on numpad location style
    if (quadrant1)
      answer = helper::minf(answer, box(point - cornerOpposite, sharpSizeHalf));

    if (quadrant7)
      answer = helper::minf(answer, box(point - cornerSame, sharpSizeHalf));

    if (quadrant9)
      answer = helper::minf(answer, box(point + cornerOpposite, sharpSizeHalf));

    if (quadrant3)
      answer = helper::minf(answer, box(point + cornerSame, sharpSizeHalf));

    return answer;
  }

};


#endif //RAYMARCHER_SIGNEDDISTANCE_H
