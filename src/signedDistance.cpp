//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//

#include "signedDistance.h"

namespace signedDistance {

  float box(vector point, vector size) {
    vector distance        = point.abs() - size;
    float externalDistance = distance.max(0.0f).length();
    float internalDistance = helper::minf(0.0f, helper::maxf(distance.x, distance.y, distance.z));
    return externalDistance + internalDistance;
  }


  float mhcpLogoCylinder(vector point) {
    point.z += helper::clamp(point.z, 0.0f, -0.25f);   // hardcoded line segment distance
    float distance = point.length() - 1.8f;                      // make it into capsule by using the sphere calculation
    return helper::maxf(distance, -point.z - 0.25f, point.z);     // flatten ends with planes to make a cylinder
  }

};

