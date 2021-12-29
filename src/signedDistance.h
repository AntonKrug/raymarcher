//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//


#ifndef RAYMARCHER_SIGNEDDISTANCE_H
#define RAYMARCHER_SIGNEDDISTANCE_H

#include <limits>

#include "vector.h"
#include "helper.h"

namespace signedDistance {

  float box(vector point, vector size);
  float mhcpLogoCylinder(vector point);

  template<bool quadrant1, bool quadrant7, bool quadrant9, bool quadrant3>
  float mhcpDodlyDood(vector point, vector size) {
    // First calculating the whole box with smooth rounded courners
    float roundNess = 0.25f; // corners rounded
    float base = box(point, vector(size.x - roundNess, size.y - roundNess, size.z)) - roundNess;

    // Able to make any of the 4 corners/quadrants sharp, the numbers are based on numpad location style
    float corner1 = std::numeric_limits<float>::max();
    float corner7 = std::numeric_limits<float>::max();
    float corner9 = std::numeric_limits<float>::max();
    float corner3 = std::numeric_limits<float>::max();

    if (quadrant1)
      corner1 = box(point - vector(+size.x / 2.0f, -size.y / 2.0f, 0.0f), size / 2.0f);

    if (quadrant7)
      corner7 = box(point - vector(+size.x / 2.0f, +size.y / 2.0f, 0.0f), size / 2.0f);

    if (quadrant9)
      corner9 = box(point - vector(-size.x / 2.0f, +size.y / 2.0f, 0.0f), size / 2.0f);

    if (quadrant3)
      corner3 = box(point - vector(-size.x / 2.0f, -size.y / 2.0f, 0.0f), size / 2.0f);

    return helper::minf(base, corner1, corner7, corner9, corner3);
  }

};


#endif //RAYMARCHER_SIGNEDDISTANCE_H
