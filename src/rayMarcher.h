//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_RAYMARCHER_H
#define RAYMARCHER_RAYMARCHER_H

#include "vector.h"
#include "color.h"

class rayMarcher {
private:
  float signedSceneDistance(vector currentPoint);
  vector getNormal(vector point);
  color sphereTracing(vector origin, vector direction);

public:
  void renderLine(int y);

};


#endif //RAYMARCHER_RAYMARCHER_H
