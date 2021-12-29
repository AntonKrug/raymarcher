//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include "mhcp.h"
#include "../signedDistance.h"
#include "../helper.h"

float mhcp::signedSceneDistance(vector point) {
  float sdBottomPlane  = point.y + 3.0f;

  float sdLogoCylinder = signedDistance::mhcpLogoCylinder(point);
  float sdLogo = sdLogoCylinder;

  if (sdLogoCylinder < 0.05f) {
    // Use the logoCylinder as boundary box and only calculate the rest of the cylinder details when the ray gets closer
    const vector logoPlaneNormal = vector(-1.0f, 0.637f, 0.0f).normalize();
    float sdLogoPlane = (point - vector(-1.9f, 0.0f, 0.0f)).dotProduct(logoPlaneNormal);

    // rotating and twisting the dodlyDood box XY space once for all 3 boxes
    vector pointRotated = point - vector(point.y * +0.637f, point.x * -0.81714f, 0.0f);

    float sdCut1 = signedDistance::mhcpDodlyDood(
        pointRotated + vector(0.1f, 0.0f, 0.0f),
        vector(0.35f, 0.95f, 2.0f));

    sdLogo = helper::maxf(sdLogoCylinder, sdLogoPlane, -sdCut1);
  }

  return helper::minf(sdBottomPlane, sdLogo);
}
