//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//

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


  float mhcpDodlyDood(vector point, vector base) {
    point = point - vector(point.y * -0.637f, point.x * 0.81714f, 0.0f);
    float roundNess = 0.25f;
    float b1  = box(point, vector(base.x - roundNess, base.y - roundNess, base.z)) - roundNess;
    float ba1 = box(point - vector(+base.x / 2.0f, -base.y / 2.0f, 0.0f) , base / 2.0f);
    float bb1 = box(point - vector(-base.x / 2.0f, +base.y / 2.0f, 0.0f), base / 2.0f);

    return helper::min3(b1, ba1, bb1);
  }


};

