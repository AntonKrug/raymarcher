//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//


#ifndef RAYMARCHER_SIGNEDDISTANCE_H
#define RAYMARCHER_SIGNEDDISTANCE_H

#include <limits>

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

    const vector size           = vector(sizeX, sizeY, 2.0f);
    const vector sizeHalf       = vector(sizeX / 2.0f, sizeY /2.0f, 2.0f);

    const vector cornerSame     = vector(+sizeX / 2.0f, +sizeY / 2.0f, 0.0f);
    const vector cornerOpposite = vector(+sizeX / 2.0f, -sizeY / 2.0f, 0.0f);

    // First calculating the whole box with smooth rounded courners
    float roundNess = 0.25f; // corners rounded
    float base = box(point, vector(size.x - roundNess, size.y - roundNess, size.z)) - roundNess;

    // Able to make any of the 4 corners/quadrants sharp, the numbers are based on numpad location style
    float corner1 = std::numeric_limits<float>::max();
    float corner7 = std::numeric_limits<float>::max();
    float corner9 = std::numeric_limits<float>::max();
    float corner3 = std::numeric_limits<float>::max();

    if (quadrant1)
      corner1 = box(point - cornerOpposite, sizeHalf);

    if (quadrant7)
      corner7 = box(point - cornerSame, sizeHalf);

    if (quadrant9)
      corner9 = box(point + cornerOpposite, sizeHalf);

    if (quadrant3)
      corner3 = box(point + cornerSame, sizeHalf);

    return helper::minf(base, corner1, corner7, corner9, corner3);
  }

};


#endif //RAYMARCHER_SIGNEDDISTANCE_H
