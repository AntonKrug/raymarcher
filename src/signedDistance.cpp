//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//

#include "signedDistance.h"

#include "helper.h"

namespace signedDistance {

  float box(vector currentPoint, vector size) {
    vector distance = currentPoint.abs() - size;
    distance.maxInPlace(0.0f);
    return distance.length();
  }


  float mhcpLogoCylinder(vector currentPoint) {
    const vector thick = vector(0.0f, 0.0f, -0.25f);
    const vector thickNormalized = vector(thick).normalize();

    vector closePoint = thickNormalized.multiplyConst(currentPoint.dotProduct(thick));
    float  distance   = (currentPoint - closePoint).length() - 1.8f;

    return helper::fmaxfast3(distance, -currentPoint.z - 0.25, currentPoint.z);
  }


};

