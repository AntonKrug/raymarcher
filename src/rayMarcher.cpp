//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "rayMarcher.h"

#include "config.h"
#include "outputSdl.h"
#include "sampler.h"


const auto sampleLookupTable = Sampler::populateSampleTable<0>();


float rayMarcher::signedSceneDistance(vector currentPoint) {
  vector sphere(5.0f,1.0f,2.0f);

  return (currentPoint - sphere).length() -1.0f;
}


void rayMarcher::renderLine(int y) {
    vector cameraOrigin(-3, 4, -5);

    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      color color = sphereTracing(cameraOrigin, vector(x * stepX + 1.0f, y * stepY - 0.5f, 1.0f).normalize());
      outputSdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();
    }
}


color rayMarcher::sphereTracing(vector origin, vector direction) {
  float distanceTotal = 0.0f;
  vector lightPosition(0, 5, 0);

  for (int step=0; step < config::traceMaxSteps; step++) {
    vector currentPoint    = origin + direction * distanceTotal;
    float distanceToObject = signedSceneDistance(currentPoint);
    distanceTotal+=distanceToObject;

    if (distanceToObject < config::minObjectDistance) {
      vector normal         = getNormal(currentPoint);
      vector lightDirection = (lightPosition - currentPoint).normalize();
      return color(normal.dotProduct(lightDirection)).clamp();
    }
    else if (distanceTotal > config::traceMaxDistance) {
      return color(0.0f);
    }
  }

  return color(0.0f);
}


vector rayMarcher::getNormal(vector point) {
  float distance = signedSceneDistance(point);

  vector normal(
      signedSceneDistance(point.nudgeX()),
      signedSceneDistance(point.nudgeY()),
      signedSceneDistance(point.nudgeZ()));

  return (normal - distance).normalize();
}
