//
// Created by anton.krug@gmail.com on 28/12/21.
// License: MIT
//

#include <limits>

#include "mhcp.h"

#include "../signedDistance.h"


float mhcp::signedDistance(vector point) {
  float sdBottomPlane  = point.y + 2.5f;

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

  constexpr int radiusInt = 80;
  float sdLetter = std::numeric_limits<float>::max();

  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-102	,	864	, radiusInt>(point, vector(	2.86	,	-2.002	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-330	,	-738	, radiusInt>(point, vector(	2.758	,	-1.138	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-324	,	738	, radiusInt>(point, vector(	2.428	,	-1.876	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-114	,	-864	, radiusInt>(point, vector(	2.104	,	-1.138	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	1.726	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	456	,	0	, radiusInt>(point, vector(	0.994	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	1.45	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-456	,	0	, radiusInt>(point, vector(	1.45	,	-2.002	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	0.73	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-462	,	0	, radiusInt>(point, vector(	0.73	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-354	, radiusInt>(point, vector(	0.268	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	462	,	0	, radiusInt>(point, vector(	0.268	,	-1.726	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-222	,	-276	, radiusInt>(point, vector(	0.490000000000001	,	-1.726	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-498	,	0	, radiusInt>(point, vector(	-0.002	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	-0.5	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	498	,	0	, radiusInt>(point, vector(	-0.5	,	-2.002	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	630	, radiusInt>(point, vector(	-0.002	,	-2.002	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	462	,	0	, radiusInt>(point, vector(	-1.22	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	-0.758	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-462	,	0	, radiusInt>(point, vector(	-0.758	,	-2.002	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	-1.478	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-468	,	0	, radiusInt>(point, vector(	-1.478	,	-1.636	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	-1.946	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	-630	, radiusInt>(point, vector(	-2.204	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	0	,	630	, radiusInt>(point, vector(	-2.468	,	-2.002	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-342	,	0	, radiusInt>(point, vector(	-2.468	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	-150	,	-198	, radiusInt>(point, vector(	-2.81	,	-1.372	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	150	,	-174	, radiusInt>(point, vector(	-2.96	,	-1.57	,	0.6	)));
  sdLetter = helper::minf(sdLetter, signedDistance::capsuleDeltaCt<	342	,	0	, radiusInt>(point, vector(	-2.81	,	-1.744	,	0.6	)));

  return helper::minf(sdBottomPlane, sdLogo, sdLetter);
}
