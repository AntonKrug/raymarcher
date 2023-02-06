//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include <cmath>

#include "mchp.h"

#include "../signedDistance.h"


std::tuple<float,  materialE> mchp::signedDistance(vector point) {
  constexpr float boundaryBoxThreshold = 0.02f;

  // Top and 'behind camera' skybox to limit the marching
  if (point.y > 12.0f) {
    return std::make_tuple(0.0f, materialE::skyBoxWhite);
  }

  if (point.z > 12.0f) {
    return std::make_tuple(0.0f, materialE::skyBoxBlack);
  }

  // Bottom ground plane
  materialE answerMaterial = materialE::ground;
  float     answerDistance = point.y + 2.5f;

  // Same material as ground, blob
  float sdBlobs   = signedDistance::sphereCt<2350, 150, -600, 970>(point);

  if (sdBlobs < boundaryBoxThreshold) {
    // Boundary 'box' sphere to hide the smooth min function from most of the rays
    float sdBlob1 = signedDistance::sphereCt<2000, 300, -1100, 400>(point);
    float sdBlob2 = signedDistance::box(point - vector(2.6f, 0.0f, -0.7f), vector(0.3f, 0.3f, 0.3f));
    float sdBlob3 = signedDistance::sphereCt<2600, 0, -700, 400>(point);

    sdBlobs = helper::maxf(helper::smoothMin<400>(sdBlob1, sdBlob2), -sdBlob3);
    if (sdBlobs < answerDistance) {
      answerMaterial = materialE::objectBlob;
    }
  }
  answerDistance = helper::minf(answerDistance, sdBlobs);

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

  // MCHP text
  constexpr int letterRadiusInt = 70;
  float sdLetter = signedDistance::capsuleCt<2860, -1570, 600, -5820, 0, letterRadiusInt + 432>(point);
  if (sdLetter < boundaryBoxThreshold) {
    // Using dedicated capsule as boundary box to make sure the details are not computed when
    // not really needed on rays which do not get close enough anyway

    // The boundary box capsule is not part of the image, but we are inside it, so start from scratch to
    // calculate the letters inside this capsule
    sdLetter = std::numeric_limits<float>::max();
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  2.860f, -2.002f, 0.600f, -0.102f,  0.864f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  2.758f, -1.138f, 0.600f, -0.330f, -0.738f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  2.428f, -1.876f, 0.600f, -0.324f,  0.738f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  2.104f, -1.138f, 0.600f, -0.114f, -0.864f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  1.726f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  0.994f, -1.372f, 0.600f,  0.456f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  1.450f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  1.450f, -2.002f, 0.600f, -0.456f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  0.730f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  0.730f, -1.372f, 0.600f, -0.462f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  0.268f, -1.372f, 0.600f,  0.000f, -0.354f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  0.268f, -1.726f, 0.600f,  0.462f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt<  0.490f, -1.726f, 0.600f, -0.222f, -0.276f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -0.002f, -1.372f, 0.600f, -0.498f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -0.500f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -0.500f, -2.002f, 0.600f,  0.498f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -0.002f, -2.002f, 0.600f,  0.000f,  0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -1.220f, -1.372f, 0.600f,  0.462f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -0.758f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -0.758f, -2.002f, 0.600f, -0.462f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -1.478f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -1.478f, -1.636f, 0.600f, -0.468f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -1.946f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -2.204f, -1.372f, 0.600f,  0.000f, -0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -2.468f, -2.002f, 0.600f,  0.000f,  0.630f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -2.468f, -1.372f, 0.600f, -0.342f,  0.000f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -2.810f, -1.372f, 0.600f, -0.150f, -0.198f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -2.960f, -1.570f, 0.600f,  0.150f, -0.174f >(point));
    sdLetter = helper::minf(sdLetter, signedDistance::lineSquaredCt< -2.810f, -1.744f, 0.600f,  0.342f,  0.000f >(point));

    // Calculate the square root only on the final squared line distance and turn it into capsule distance just once
    sdLetter = helper::maxf(sqrtf(sdLetter) - floatInt<letterRadiusInt>::value, (point.z - 0.655f));
    if (sdLetter < answerDistance) {
      answerMaterial = materialE::objectLetter;
    }
  }
  answerDistance = helper::minf(answerDistance, sdLetter);

  return std::make_tuple(answerDistance, answerMaterial);
}
