//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include "mhcp.h"
#include "../signedDistance.h"
#include "../helper.h"

float mhcp::signedSceneDistance(vector currentPoint) {
  float plane  = currentPoint.y + 3.0f;

  float logoCylinder = signedDistance::mhcpLogoCylinder(currentPoint);
  float logoDistance = logoCylinder;

  if (logoCylinder < 0.05f) {
    // Use the logoCylinder as boundary box and only calculate the rest of the cylinder details when the ray gets closer
    float logoPlane = (currentPoint - vector(-1.9f, 0.0f, 0.0f)).dotProduct(vector(-1.0f, 0.637f, 0.0f).normalize());
    float cut1 = signedDistance::mhcpDodlyDood(
        currentPoint + vector(0.1f,0.0f,0.0f),
        vector(0.35f, 0.95f, 2.0f));

    logoDistance = helper::maxf(logoCylinder, logoPlane, -cut1);
  }

  return helper::minf(plane, logoDistance);
}
