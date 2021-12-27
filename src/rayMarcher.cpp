//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <limits>
#include "rayMarcher.h"

#include "config.h"
#include "outputSdl.h"
#include "sampler.h"
#include "helper.h"
#include "signedDistance.h"


const auto sampleLookupTable = Sampler::populateSampleTable<0>();


float rayMarcher::signedSceneDistance(vector currentPoint) {
  float sphere = currentPoint.length() -1.0f;
  float plane  = currentPoint.y + 3.0f;

  float logoCylinder = signedDistance::mhcpLogoCylinder(currentPoint);

  float answer = helper::fminfast2(plane, logoCylinder);

  return answer;
}


void rayMarcher::renderLine(int y) {
    vector cameraOrigin(4, 3, 5);

    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      color color;
      for (int sample = 0; sample < config::maxSamples; sample++) {
         color += sphereTracing(cameraOrigin, vector(
            (config::width/2  - x + std::get<0>(sampleLookupTable[sample])) * stepX - 0.8f,
            (config::height/2 - y + std::get<1>(sampleLookupTable[sample])) * stepY - 0.7f,
            -1.0f).normalize());

        outputSdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();

      }
    }
}


color rayMarcher::sphereTracing(vector origin, vector direction) {
  float distanceTotal = 0.0f;
  vector lightPosition(-2, 6, 4);

  for (int step=0; step < config::traceMaxSteps; step++) {
    vector currentPoint    = origin + direction * distanceTotal;
    float distanceToObject = signedSceneDistance(currentPoint);
    distanceTotal+=distanceToObject;

    if (distanceToObject < config::minObjectDistance) {
      currentPoint          = origin + direction * distanceTotal;
      vector lightDirection = (lightPosition - currentPoint).normalize();
      vector normal         = getNormal(currentPoint);
      float  diffuse        = helper::clamp(normal.dotProduct(lightDirection), 0.0f, 1.0f);
      return color(diffuse);

    } else if (distanceTotal > config::traceMaxDistance) {
      return color(0.0f);
    }
  }

  return color(0.0f);
}


vector rayMarcher::getNormal(vector point) {
  float distanceToObject = signedSceneDistance(point);

  vector normal(signedSceneDistance(point.nudgeX()),
                signedSceneDistance(point.nudgeY()),
                signedSceneDistance(point.nudgeZ()));

  return (normal - distanceToObject).normalize();
}
