//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//

#include <limits>

#include "signedDistance.h"

#include "helper.h"

namespace signedDistance {

  float box(vector point, vector size) {
    vector distance        = point.abs() - size;
    float externalDistance = distance.max(0.0f).length();
    float internalDistance = helper::min(0.0f, helper::max3(distance.x, distance.y, distance.z));
    return externalDistance + internalDistance;
  }


  float mhcpLogoCylinder(vector point) {
    point.z += helper::clamp(point.z, 0.0f, -0.25f);   // hardcoded line segment distance
    float distance = point.length() - 1.8f;                      // make it into capsule by using the sphere calculation
    return helper::max3(distance, -point.z - 0.25, point.z);  // flatten ends with planes to make a cylinder
  }


  float mhcpDodlyDood(vector point, vector size) {
    point = point - vector(point.y * +0.637f, point.x * -0.81714f, 0.0f); // rotating and twisting the box

    // First calculating the whole box with smooth rounded courners
    float roundNess = 0.25f; // corners rounded
    float base = box(point, vector(size.x - roundNess, size.y - roundNess, size.z)) - roundNess;

    // Able to make any of the 4 corners/quadrants sharp, the numbers are based on numpad location style
    float corner1 = std::numeric_limits<float>::max();
    float corner7 = std::numeric_limits<float>::max();
    float corner9 = std::numeric_limits<float>::max();
    float corner3 = std::numeric_limits<float>::max();

//    corner1 = box(point - vector(+size.x / 2.0f, -size.y / 2.0f, 0.0f), size / 2.0f);
    corner7 = box(point - vector(+size.x / 2.0f, +size.y / 2.0f, 0.0f), size / 2.0f);
//    corner9 = box(point - vector(-size.x / 2.0f, +size.y / 2.0f, 0.0f), size / 2.0f);
    corner3 = box(point - vector(-size.x / 2.0f, -size.y / 2.0f, 0.0f), size / 2.0f);

    return helper::min5(base, corner1, corner7, corner9, corner3);
  }


};

