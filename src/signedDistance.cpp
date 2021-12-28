//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//

#include "signedDistance.h"

#include "helper.h"

namespace signedDistance {

  float box(vector currentPoint, vector size) {
    vector distance = currentPoint.abs() - size;
    float externalDistance = distance.max(0.0f).length();
    float internalDistance = helper::fminfast2(0.0f, helper::fmaxfast3(distance.x, distance.y, distance.z));
    return externalDistance + internalDistance;
  }


  float mhcpLogoCylinder(vector currentPoint) {
    const vector thick = vector(0.0f, 0.0f, -0.25f);
    const vector thickNormalized = vector(thick).normalize();

    vector closePoint = thickNormalized.multiplyConst(currentPoint.dotProduct(thick));
    float  distance   = (currentPoint - closePoint).length() - 1.8f;

    return helper::fmaxfast3(distance, -currentPoint.z - 0.25, currentPoint.z);
  }


  float mhcpDodlyDood(vector currentPoint, vector base) {
    currentPoint = currentPoint - vector(currentPoint.y * -0.637f, currentPoint.x * 0.81714f, 0.0f);
    float roundNess = 0.25f;
    float b1  = box(currentPoint, vector(base.x-roundNess, base.y-roundNess, base.z))-roundNess;
    float ba1 = box(currentPoint -vector(+base.x/2.0f, -base.y/2.0f, 0.0f) , base/2.0f);
    float bb1 = box(currentPoint -vector(-base.x/2.0f, +base.y/2.0f, 0.0f), base/2.0f);

    return helper::fminfast3(b1,ba1,bb1);
  }


};

