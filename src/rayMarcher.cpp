//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <limits>

#include "rayMarcher.h"

#include "scenes/mhcp.h"

#include "helper.h"
#include "outputSdl.h"
#include "sampler.h"


const auto sampleLookupTable = Sampler::populateSampleTable<0>();

float rayMarcher::signedSceneDistance(vector currentPoint) {
  return mhcp::signedSceneDistance(currentPoint);
}


void rayMarcher::renderLine(int y) {
    vector cameraOrigin(4, 3, 5);

    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      color color;
      for (int sample = 0; sample < config::maxSamples; sample++) {
         color += shadePixel(cameraOrigin, vector(
            (config::width/2  - x + std::get<0>(sampleLookupTable[sample])) * stepX - 0.8f,
            (config::height/2 - y + std::get<1>(sampleLookupTable[sample])) * stepY - 0.7f,
            -1.0f).normalize());

        outputSdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();

      }
    }
}


std::tuple<float, vector> rayMarcher::sphereTracing(vector origin, vector direction) {
  float distanceTotal = 0.0f;
  vector currentPoint = origin;

  for (int step=0; step < config::traceMaxSteps; step++) {
    float distanceToObject  =  signedSceneDistance(currentPoint);
    distanceTotal          += distanceToObject;
    currentPoint            = origin + direction * distanceTotal;

    if (distanceToObject < config::minObjectDistance) break;
  }

  return std::make_tuple(distanceTotal, currentPoint);
}


color rayMarcher::shadePixel(vector origin, vector direction) {
  vector lightPosition(-2, 6, 4);

  auto [_, hitpoint] = sphereTracing(origin, direction);

  // calculate diffuse color
  vector lightDirection = (lightPosition - hitpoint).normalize();
  vector normal         = getNormal(hitpoint);
  float  diffuse        = helper::clamp(normal.dotProduct(lightDirection), 0.0f, 1.0f);

  // calculate shadow
  auto [lightDistance, __]   = sphereTracing(hitpoint + normal * 0.1f, lightDirection);
  if (lightDistance < (lightPosition - hitpoint).length()) diffuse *= 0.25f;

  return color(diffuse);
}


vector rayMarcher::getNormal(vector point) {
  float distanceToObject = signedSceneDistance(point);

  vector normal(signedSceneDistance(point.nudgeX()),
                signedSceneDistance(point.nudgeY()),
                signedSceneDistance(point.nudgeZ()));

  return (normal - distanceToObject).normalize();
}
