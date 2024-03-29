//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_RAYMARCHER_H
#define RAYMARCHER_RAYMARCHER_H

#include "tuple"

#include "scenes/scene.h"
#include "vector.h"
#include "helper.h"
#include "color.h"
#include "outputSdl.h"
#include "sampler.h"
#include "materialE.h"

template <class SCENE>
class rayMarcher {

private:

  static vector getNormal(vector point) {
    auto [distanceToObject, _] = SCENE::signedDistance(point);

    const auto [normalX, __]   = SCENE::signedDistance(point.nudgeX());
    const auto [normalY, ___]  = SCENE::signedDistance(point.nudgeY());
    const auto [normalZ, ____] = SCENE::signedDistance(point.nudgeZ());

    vector normal(normalX, normalY, normalZ);

    return (normal - distanceToObject).normalize();
  }


  static std::tuple<float, vector, materialE> sphereTracing(vector origin, vector direction) {
    float distanceTotal = 0.0f;
    vector currentPoint = origin;
    materialE answerMaterial;

    for (int step=0; step < config::traceMaxSteps; step++) {
      auto [distanceToObject, materialOfObject]  = SCENE::signedDistance(currentPoint);
      answerMaterial                             = materialOfObject;
      distanceTotal                             += distanceToObject;
      currentPoint                               = origin + direction * distanceTotal;

      if (distanceToObject < config::minObjectDistance || distanceTotal >= config::traceMaxDistance) break;
    }

    return std::make_tuple(distanceTotal, currentPoint, answerMaterial);
  }


  static color shadePixel(vector origin, vector direction) {
    color answer(0.0f);
    float fadeFromBounce = 1.0f;

    for (int bounceCount = 0; bounceCount < config::maxBounce; bounceCount++) {
      auto [_, hitpoint, material] = sphereTracing(origin, direction);

      // calculate diffuse color
      vector lightDirection = (SCENE::getLightPosition() - hitpoint).normalize();
      vector normal         = getNormal(hitpoint);
      float  diffuse        = helper::clamp(normal.dotProduct(lightDirection), 0.0f, 1.0f);
      color  currentColor(0.0f);

      // calculate shadow
      auto [lightDistance, __, materialSky] = sphereTracing(hitpoint + normal * 0.1f, lightDirection);

      // if the calculated ray distance is shorther than the ideal distance, then it means
      // the ray did something on the way and therefore it must be covered in a shadow
      if (materialSky != materialE::skyBoxWhite) {
        if (lightDistance < (SCENE::getLightPosition() - hitpoint).length()) diffuse *= 0.25f;
      }

      switch (material) {
        case materialE::skyBoxBlack:
          bounceCount = config::maxBounce;
          break;

        case materialE::skyBoxWhite:
          answer += color(15.0f, 15.0f, 13.0f) * fadeFromBounce;
          break;

        case materialE::ground:
          if ((abs((int)(hitpoint.x * 0.8f - 100.6f)) % 2) ^ (abs((int)(hitpoint.z * 1.1f)) % 2)) {
            answer += color(1.0f, 1.0f, 1.87f) * diffuse * fadeFromBounce;
          } else {
            answer += color(3.33f) * diffuse * fadeFromBounce;
          }
          bounceCount = config::maxBounce;
          break;

        case materialE::wall:
          answer += color(0.6f, 1.0f, 0.7f) * diffuse * fadeFromBounce;
          bounceCount = config::maxBounce;
          break;

        case materialE::objectRed:
          answer += color(16.0f, 0.4f, 0.6f) * diffuse * fadeFromBounce;
          direction -= normal * 2 * normal.dotProduct(direction);
          origin = hitpoint + direction * 0.1f;
          fadeFromBounce *= 0.35f;
          break;

        case materialE::objectLetter:
          answer += color(0.5f, 0.2f,0.2f) * diffuse * fadeFromBounce;
          direction -= normal * 2 * normal.dotProduct(direction);
          origin = hitpoint + direction * 0.1f;
          fadeFromBounce *= 0.2f;
          break;

        case materialE::objectBlob:
          answer += color(3.33f) * diffuse * fadeFromBounce;
          bounceCount = config::maxBounce;
          break;


        default:
          break;
      }
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
        vector rayDirection = SCENE::getCameraDirection() +
            SCENE::getCameraRightPixel() * (-config::width/2 + x + std::get<0>(sampler::lutBoth[sample])) +
            SCENE::getCameraDownPixel()  * (-config::width/2 + y + std::get<1>(sampler::lutBoth[sample]));

        color += shadePixel(SCENE::getCameraOrigin(), rayDirection.normalize());

        outputSdl::pixels[(config::width * y) + x] = color.hdrToNormalizedLdrARGB8888();

      }
    }
  }


};


#endif //RAYMARCHER_RAYMARCHER_H
