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
  return currentPoint.length() -1.0f;
}


void rayMarcher::renderLine(int y) {
    vector cameraOrigin(0, 1, -3);

    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      color color = sphereTracing(cameraOrigin, vector(
          (config::width/2 - x) * stepX,
          (config::height/2 - y) * stepY - 0.2f,
          1.0f).normalize());

      outputSdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();
    }
}


color rayMarcher::sphereTracing(vector origin, vector direction) {
  float distanceTotal = 0.0f;
  vector lightPosition(0, 3, 0);

  for (int step=0; step < config::traceMaxSteps; step++) {
    vector currentPoint    = origin + direction * distanceTotal;
    float distanceToObject = signedSceneDistance(currentPoint);
    distanceTotal+=distanceToObject;

    if (distanceToObject < config::minObjectDistance) {
//      return color(distanceTotal).clamp();
      currentPoint          = origin + direction * distanceTotal;
      vector lightDirection = (lightPosition - currentPoint).normalize();
      vector normal         = getNormal(currentPoint);
      float  diffuse        = normal.dotProduct(lightDirection) * 2.0f;
      return color(0.0f, diffuse, 0.0f);
    }
    else if (distanceTotal > config::traceMaxDistance) {
      return color(0.0f);
    }
  }

  return color(0.0f);
}


vector rayMarcher::getNormal(vector point) {
  float distanceToObject = signedSceneDistance(point);

  vector offsetX(config::nudgeOffset, 0.0f, 0.0f);
  vector offsetY(0.0f, config::nudgeOffset, 0.0f);
  vector offsetZ(0.0f, 0.0f, config::nudgeOffset);

  vector px(point - offsetX);
  vector py(point - offsetY);
  vector pz(point - offsetZ);

  float dx = signedSceneDistance(px);
  float dy = signedSceneDistance(py);
  float dz = signedSceneDistance(pz);

  vector normal(dx, dy, dz);

  normal = normal * -1.0f + distanceToObject;

  return normal.normalize();
}