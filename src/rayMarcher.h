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
  static float signedSceneDistance(vector currentPoint);
  static vector getNormal(vector point);
  static color sphereTracing(vector origin, vector direction);

public:
  static void renderLine(int y);

};


#endif //RAYMARCHER_RAYMARCHER_H
