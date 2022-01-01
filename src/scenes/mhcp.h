//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#ifndef RAYMARCHER_MHCP_H
#define RAYMARCHER_MHCP_H

#include "../vector.h"
#include "../config.h"


struct mhcp {
  inline static vector cameraOrigin    = vector(4.0f, 1.5f, 5.0f);
  inline static vector cameraDirection = vector(-4.0f, -2.5f, -5.0f).normalize();

  inline static vector cameraRightPixel = vector(cameraDirection.z, cameraDirection.y, -cameraDirection.x).normalize() / config::width;
  inline static vector cameraDownPixel  = cameraRightPixel.crossProduct(cameraDirection);

  inline static vector lightPosition   = vector(-2.0f, 6.0f, 4.0f);

  static float signedDistance(vector point);
};


#endif //RAYMARCHER_MHCP_H
