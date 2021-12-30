//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include <limits>

#include "mhcp.h"

#include "../signedDistance.h"


float mhcp::signedDistance(vector point) {
  float sdBottomPlane  = point.y + 3.2f;

  float sdLogoCylinder = signedDistance::mhcpLogoCylinder(point);
  float sdLogo = sdLogoCylinder;

  if (sdLogoCylinder < 0.02f) {
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

  constexpr int radiusInt = 130;
  float sdLetter = std::numeric_limits<float>::max();

  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-170	,	1440	, radiusInt>(point, vector(	4.65	,	-2.67	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-550	,	-1230	, radiusInt>(point, vector(	4.48	,	-1.23	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-540	,	1230	, radiusInt>(point, vector(	3.93	,	-2.46	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-190	,	-1440	, radiusInt>(point, vector(	3.39	,	-1.23	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	2.76	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	760	,	0	, radiusInt>(point, vector(	1.54	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	2.3	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-760	,	0	, radiusInt>(point, vector(	2.3	,	-2.67	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	1.1	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-770	,	0	, radiusInt>(point, vector(	1.1	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-590	, radiusInt>(point, vector(	0.329999999999999	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	770	,	0	, radiusInt>(point, vector(	0.329999999999999	,	-2.21	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-370	,	-460	, radiusInt>(point, vector(	0.7	,	-2.21	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-830	,	0	, radiusInt>(point, vector(	-0.12	,	-1.64	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1030	, radiusInt>(point, vector(	-0.95	,	-1.64	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	830	,	0	, radiusInt>(point, vector(	-0.95	,	-2.67	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	1030	, radiusInt>(point, vector(	-0.12	,	-2.67	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	770	,	0	, radiusInt>(point, vector(	-2.15	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	-1.38	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-770	,	0	, radiusInt>(point, vector(	-1.38	,	-2.67	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	-2.58	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-780	,	0	, radiusInt>(point, vector(	-2.58	,	-2.06	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	-3.36	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-1050	, radiusInt>(point, vector(	-3.79	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	1050	, radiusInt>(point, vector(	-4.23	,	-2.67	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-570	,	0	, radiusInt>(point, vector(	-4.23	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-250	,	-330	, radiusInt>(point, vector(	-4.8	,	-1.62	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	250	,	-290	, radiusInt>(point, vector(	-5.05	,	-1.95	,	0.7	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	570	,	0	, radiusInt>(point, vector(	-4.8	,	-2.24	,	0.7	)));

  return helper::minf(sdBottomPlane, sdLogo, sdLetter);
}
