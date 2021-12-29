//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#ifndef RAYMARCHER_MHCP_H
#define RAYMARCHER_MHCP_H

#include "../vector.h"


struct mhcp {
  inline static vector cameraOrigin    = vector(4.0f, 3.0f, 5.0f);
  inline static vector cameraDirection = vector(- 0.8f, - 0.7f, -1.0f);

  inline static vector lightPosition   = vector(-2.0f, 6.0f, 4.0f);

  static float signedDistance(vector point);
};


#endif //RAYMARCHER_MHCP_H
