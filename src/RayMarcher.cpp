//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "RayMarcher.h"

#include "config.h"
#include "Sdl.h"


float sceneDistance(Vector currentPoint) {
  Vector sphere(5.0f,1.0f,2.0f);

  return (currentPoint - sphere).length() -1.0f;
}


void RayMarcher::renderLine(int y) {
    Vector cameraOrigin(-3, 4, -5);

    float stepX = 1.0f / config::width;
    float stepY = 1.0f / config::height;

    for (int x = 0; x < config::width; x++) {
      Color color = sphereTracing(cameraOrigin, Vector(x * stepX + 1.0f, y * stepY - 0.5f, 1.0f).normalize());
      Sdl::pixels[(config::width * y) + x] = color.toNormalizedARGB888();
    }
}


Color RayMarcher::sphereTracing(Vector origin, Vector direction) {
  float distanceTotal = 0.0f;
  Vector lightPosition(0, 5, 0);

  for (int step=0; step < config::traceMaxSteps; step++) {
    Vector currentPoint    = origin + direction * distanceTotal;
    float distanceToObject = signedSceneDistance(currentPoint);
    distanceTotal+=distanceToObject;

    if (distanceToObject < config::minObjectDistance) {
      Vector normal         = getNormal(currentPoint);
      Vector lightDirection = (lightPosition - currentPoint).normalize();
      return Color(normal.dotProduct(lightDirection)).clamp();
    }
    else if (distanceTotal > config::traceMaxDistance) {
      return Color(0.0f);
    }
  }

}


Vector RayMarcher::getNormal(Vector point) {
  float distance = sceneDistance(point);

  Vector normal(
      signedSceneDistance(point.nudgeX()),
      signedSceneDistance(point.nudgeY()),
      signedSceneDistance(point.nudgeZ()));

  return (normal - distance).normalize();
}
