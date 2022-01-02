//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#ifndef RAYMARCHER_MHCP_H
#define RAYMARCHER_MHCP_H

#include <tuple>

#include "../vector.h"
#include "../config.h"
#include "../materialE.h"


struct mhcp {
  inline static vector cameraOrigin     = vector(3.0f, 1.5f, 4.5f);
  inline static vector cameraDirection  = vector(-2.2f, -2.1f, -4.5f).normalize();

  // http://learnwebgl.brown37.net/07_cameras/camera_introduction.html
  inline static vector cameraRightPixel = vector(cameraDirection.z, +0.3f, -cameraDirection.x).normalize() / config::width;
  inline static vector cameraDownPixel  = cameraRightPixel.crossProduct(cameraDirection);

  inline static vector lightPosition    = vector(-2.0f, 6.0f, 4.0f);

  static std::tuple<float,  materialE> signedDistance(vector point);
};


#endif //RAYMARCHER_MHCP_H
