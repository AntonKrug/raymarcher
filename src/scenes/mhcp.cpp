//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include <limits>

#include "mhcp.h"

#include "../signedDistance.h"


float mhcp::signedDistance(vector point) {
  constexpr float boundaryBoxThreshold = 0.02f;
  float sdBottomPlane  = point.y + 2.5f;

  float sdLogoCylinder = signedDistance::mhcpLogoCylinder(point);
  float sdLogo = sdLogoCylinder;

  if (sdLogoCylinder < boundaryBoxThreshold) {
    // Use the logoCylinder as boundary box and only calculate the rest of the cylinder details when the ray gets closer
    const vector logoPlaneNormal = vector(-1.0f, 0.637f, 0.0f).normalize();
    float sdLogoPlane = (point - vector(-1.7f, 0.0f, 0.0f)).dotProduct(logoPlaneNormal);

    // rotating and twisting the dodlyDood box XY space once for all 3 boxes
    vector pointRotated = point - vector(point.y * +0.637f, point.x * -0.81714f, 0.0f);

    float sdCutMiddle = signedDistance::mhcpDodlyDood<400, 1300, false, true,  false, true>(
        pointRotated + vector(-0.2f, -0.1f, 0.0f));

    float sdCutRight  = signedDistance::mhcpDodlyDood<400, 2000, false, true,  false, false>(
        pointRotated + vector(0.94f, 1.52f, 0.0f));

    float sdCutLeft   = signedDistance::mhcpDodlyDood<900, 500,  false, false, true,  false>(
        pointRotated + vector(-1.855f, -0.91f, 0.0f));

    float sdCuts = helper::minf(sdCutMiddle, sdCutRight, sdCutLeft);

    sdLogo = helper::maxf(sdLogoCylinder, sdLogoPlane, -sdCuts);
  }

  constexpr int letterRadiusInt = 70;
  float sdLetter = signedDistance::capsuleDeltaCt<	-5820	,	0	, letterRadiusInt + 432		>(point, vector(2.86	, -1.57	, 0.6	));
  if (sdLetter < boundaryBoxThreshold) {
    // Using dedicate capsule as boundary box to make sure the details are not computed when
    // not really needed on rays which do not get close enough anyway

    sdLetter = std::numeric_limits<float>::max(); // the BB capsule is not part of the image, start from scratch
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-102, +864, 2860, -2002, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-330, -738, 2758, -1138, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-324, +738, 2428, -1876, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-114, -864, 2104, -1138, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, 1726, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+456, +0, 994, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, 1450, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-456, +0, 1450, -2002, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, 730, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-462, +0, 730, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -354, 268, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+462, +0, 268, -1726, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-222, -276, 490, -1726, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-498, +0, -2, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, -500, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+498, +0, -500, -2002, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, +630, -2, -2002, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<462, +0, -1220, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, -758, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-462, +0, -758, -2002, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, -1478, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-468, +0, -1478, -1636, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, -1946, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, -630, -2204, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+0, +630, -2468, -2002, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<-342, +0, -2468, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter,
                            signedDistance::capsuleAllCt<-150, -198, -2810, -1372, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter,
                            signedDistance::capsuleAllCt<+150, -174, -2960, -1570, 600, letterRadiusInt>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::capsuleAllCt<+342, +0, -2810, -1744, 600, letterRadiusInt>(point));

  }



  return helper::minf(sdBottomPlane, sdLogo, sdLetter);
}
