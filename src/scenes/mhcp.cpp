//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include <cmath>

#include "mhcp.h"

#include "../signedDistance.h"


std::tuple<float,  materialE> mhcp::signedDistance(vector point) {
  constexpr float boundaryBoxThreshold = 0.02f;

  // Bottom ground plane
  materialE answerMaterial = materialE::ground;
  float answerDistance = point.y + 2.5f;

  // Same material as ground, blob
  float sdBlobs       = signedDistance::sphereCt<2350, 150, -600, 970>(point);

  if (sdBlobs < boundaryBoxThreshold) {
    // Boundary 'box' sphere to hide the smooth min function from most of the rays
    float sdBlob1       = signedDistance::sphereCt<2000, 300, -1100, 400>(point);
    float sdBlob2       = signedDistance::box(point - vector(2.6f, 0.0f, -0.7f), vector(0.3f, 0.3f, 0.3f));
    float sdBlob3       = signedDistance::sphereCt<2600, 0, -700, 400>(point);

    sdBlobs = helper::maxf(helper::smoothMin<600>(sdBlob1, sdBlob2), -sdBlob3);
  }
  answerDistance = helper::minf(answerDistance, sdBlobs);

  // Top and 'behind camera' skybox to limit the marching
//  float sdSkyPlane = helper::minf(-point.y + 12.0f, -point.z + 12.0f);
  float sdSkyPlane = -point.y + 12.0f;
  if (sdSkyPlane < answerDistance) {
    answerDistance = sdSkyPlane;
    answerMaterial = materialE::skyBoxWhite;
  }

  // Back wall
  float sdBackPlane = point.z + 2.5f;
  if (sdBackPlane < answerDistance) {
    answerDistance = sdBackPlane;
    answerMaterial = materialE::wall;
  }

  // MHCP logo
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
    if (sdLogo < answerDistance) {
      answerMaterial = materialE::objectRed;
    }
  }
  answerDistance = helper::minf(answerDistance, sdLogo);

  // MHCP text
  constexpr int letterRadiusInt = 70;
  float sdLetter = signedDistance::capsuleCt<2860, -1570, 600, -5820, 0, letterRadiusInt + 432>(point);
  if (sdLetter < boundaryBoxThreshold) {
    // Using dedicate capsule as boundary box to make sure the details are not computed when
    // not really needed on rays which do not get close enough anyway

    // the BB capsule is not part of the image, start from scratch
    sdLetter = signedDistance::lineSquaredCt<2860,  -2002, 600, -102, 864 >(point);
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<2758,  -1138, 600, -330, -738>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<2428,  -1876, 600, -324, 738 >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<2104,  -1138, 600, -114, -864>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<1726,  -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<994,   -1372, 600, 456,  0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<1450,  -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<1450,  -2002, 600, -456, 0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<730,   -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<730,   -1372, 600, -462, 0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<268,   -1372, 600, 0,    -354>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<268,   -1726, 600, 462,  0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<490,   -1726, 600, -222, -276>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2,    -1372, 600, -498, 0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-500,  -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-500,  -2002, 600, 498,  0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2,    -2002, 600, 0,    630 >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-1220, -1372, 600, 462,  0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-758,  -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-758,  -2002, 600, -462, 0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-1478, -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-1478, -1636, 600, -468, 0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-1946, -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2204, -1372, 600, 0,    -630>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2468, -2002, 600, 0,    630 >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2468, -1372, 600, -342, 0   >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2810, -1372, 600, -150, -198>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2960, -1570, 600, 150,  -174>(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<-2810, -1744, 600, 342,  0   >(point));

    // Calculate the square root only on the final squared line distance and turn it into capsule distance just once
    sdLetter = sqrtf(sdLetter) - floatInt<letterRadiusInt>::value;
    if (sdLetter < answerDistance) {
      answerMaterial = materialE::objectLetter;
    }
  }
  answerDistance = helper::minf(answerDistance, sdLetter);

  return std::make_tuple(answerDistance, answerMaterial);
}
