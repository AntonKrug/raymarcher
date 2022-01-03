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
#include "materialE.h"


template<class Tscene>
class rayMarcher {

private:


  static vector getNormal(vector point) {
    auto [distanceToObject, _] = Tscene::signedDistance(point);

    const auto [normalX, __]   = Tscene::signedDistance(point.nudgeX());
    const auto [normalY, ___]  = Tscene::signedDistance(point.nudgeY());
    const auto [normalZ, ____] = Tscene::signedDistance(point.nudgeZ());

    vector normal(normalX, normalY, normalZ);

    return (normal - distanceToObject).normalize();
  }


  static std::tuple<float, vector, materialE> sphereTracing(vector origin, vector direction) {
    float distanceTotal = 0.0f;
    vector currentPoint = origin;
    materialE answerMaterial;

    for (int step=0; step < config::traceMaxSteps; step++) {
      auto [distanceToObject, materialOfObject]  = Tscene::signedDistance(currentPoint);
      answerMaterial                             = materialOfObject;
      distanceTotal                             += distanceToObject;
      currentPoint                               = origin + direction * distanceTotal;

      if (distanceToObject < config::minObjectDistance || distanceTotal >= config::traceMaxDistance) break;
    }

    return std::make_tuple(distanceTotal, currentPoint, answerMaterial);
  }


  static color shadePixel(vector origin, vector direction) {
    color answer(0.0f);
    float fadeFromDistance = 1.0f;

    for (int bounceCount = 0; bounceCount < config::maxBounce; bounceCount++) {
      auto [_, hitpoint, material] = sphereTracing(origin, direction);

      // calculate diffuse color
      vector lightDirection = (Tscene::lightPosition - hitpoint).normalize();
      vector normal         = getNormal(hitpoint);
      float  diffuse        = helper::clamp(normal.dotProduct(lightDirection), 0.0f, 1.0f);
      color  currentColor(0.0f);

      switch (material) {
        case materialE::ground:
          currentColor = color(0.73f, 0.83f, 0.97f);
          bounceCount = config::maxBounce;
          break;

        case materialE::wall:
          currentColor = color(0.3f, 0.7f, 0.4f);
          bounceCount = config::maxBounce;
          break;

        case materialE::objectRed:
          currentColor = color(1.0f, 0.3f, 0.3f);
          direction += normal * (normal.dotProduct(direction) * -2);
          origin = hitpoint + direction * 0.1f;
          fadeFromDistance *= 0.75f;
          break;

        case materialE::objectLetter:
          currentColor = color(0.0f, 0.0f, 0.0f);
          direction += normal * (normal.dotProduct(direction) * -2);
          origin = hitpoint + direction * 0.1f;
          fadeFromDistance *= 0.60f;
          break;

        case materialE::sky:
          currentColor = color(1.0f, 1.0f, 1.0f);
          break;

        default:
          break;
      }

      // calculate shadow
      auto [lightDistance, __, materialSky] = sphereTracing(hitpoint + normal * 0.1f, lightDirection);

      // if the calculated ray distance is shorther than the ideal distance, then it means
      // the ray did something on the way and therefore it must be covered in a shadow
      if (materialSky != materialE::sky) {
        if (lightDistance < (Tscene::lightPosition - hitpoint).length()) diffuse *= 0.25f;
      }
      answer += currentColor * diffuse * fadeFromDistance;
    }

    return answer;
  }


public:

  static void renderLine(int y) {
    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      color color;
      for (int sample = 0; sample < config::maxSamples; sample++) {
        vector rayDirection = Tscene::cameraDirection +
            Tscene::cameraRightPixel * (-config::width/2 + x + std::get<0>(sampler::lookupTable[sample])) +
            Tscene::cameraDownPixel  * (-config::width/2 + y + std::get<1>(sampler::lookupTable[sample]));

        color += shadePixel(Tscene::cameraOrigin, rayDirection.normalize());

        outputSdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();

      }
    }
  }


};


#endif //RAYMARCHER_RAYMARCHER_H
