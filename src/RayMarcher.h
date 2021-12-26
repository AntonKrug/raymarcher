//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_RAYMARCHER_H
#define RAYMARCHER_RAYMARCHER_H

#include "Vector.h"
#include "Color.h"

class RayMarcher {
private:
  float signedSceneDistance(Vector currentPoint);
  Vector getNormal(Vector point);
  Color sphereTracing(Vector origin, Vector direction);

public:
  void renderLine(int y);

};


#endif //RAYMARCHER_RAYMARCHER_H
