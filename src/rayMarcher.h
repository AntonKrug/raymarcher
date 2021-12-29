//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_RAYMARCHER_H
#define RAYMARCHER_RAYMARCHER_H

#include "tuple"

#include "vector.h"
#include "helper.h"
#include "color.h"
#include "outputSdl.h"
#include "sampler.h"


template<class Tscene>
class rayMarcher {

private:


  static vector getNormal(vector point) {
    float distanceToObject = Tscene::signedDistance(point);

    vector normal(Tscene::signedDistance(point.nudgeX()),
                  Tscene::signedDistance(point.nudgeY()),
                  Tscene::signedDistance(point.nudgeZ()));

    return (normal - distanceToObject).normalize();
  }


  static std::tuple<float, vector> sphereTracing(vector origin, vector direction) {
    float distanceTotal = 0.0f;
    vector currentPoint = origin;

    for (int step=0; step < config::traceMaxSteps; step++) {
      float distanceToObject  = Tscene::signedDistance(currentPoint);
      distanceTotal          += distanceToObject;
      currentPoint            = origin + direction * distanceTotal;

      if (distanceToObject < config::minObjectDistance) break;
    }

    return std::make_tuple(distanceTotal, currentPoint);
  }


  static color shadePixel(vector origin, vector direction) {
    auto [_, hitpoint] = sphereTracing(origin, direction);

    // calculate diffuse color
    vector lightDirection = (Tscene::lightPosition - hitpoint).normalize();
    vector normal         = getNormal(hitpoint);
    float  diffuse        = helper::clamp(normal.dotProduct(lightDirection), 0.0f, 1.0f);

    // calculate shadow
    auto [lightDistance, __] = sphereTracing(hitpoint + normal * 0.1f, lightDirection);

    // if the calculated ray distance is shorther than the ideal distance, then it means
    // the ray did something on the way and therefore it must be covered in a shadow
    if (lightDistance < (Tscene::lightPosition - hitpoint).length()) diffuse *= 0.25f;

    return color(diffuse);
  }


public:

  static void renderLine(int y) {
    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      color color;
      for (int sample = 0; sample < config::maxSamples; sample++) {
        vector direction(
            (config::width/2  - x + std::get<0>(sampler::lookupTable[sample])) * stepX + Tscene::cameraDirection.x,
            (config::height/2 - y + std::get<1>(sampler::lookupTable[sample])) * stepY + Tscene::cameraDirection.y,
            Tscene::cameraDirection.z);

        color += shadePixel(Tscene::cameraOrigin, direction.normalize());

        outputSdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();

      }
    }
  }


};


#endif //RAYMARCHER_RAYMARCHER_H
