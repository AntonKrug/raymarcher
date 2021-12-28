//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//


#ifndef RAYMARCHER_SIGNEDDISTANCE_H
#define RAYMARCHER_SIGNEDDISTANCE_H

#include "vector.h"

namespace signedDistance {

  float box(vector currentPoint, vector size);
  float mhcpLogoCylinder(vector currentPoint);
  float mhcpDodlyDood(vector currentPoint, vector base);

};


#endif //RAYMARCHER_SIGNEDDISTANCE_H
