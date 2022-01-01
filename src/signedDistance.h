//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//


#ifndef RAYMARCHER_SIGNEDDISTANCE_H
#define RAYMARCHER_SIGNEDDISTANCE_H

#include "vector.h"
#include "helper.h"
#include "cppTrickery/floatInt.h"

namespace signedDistance {

  float box(vector point, vector size);
  float capsule(vector point, vector a, vector b, const float radius);
  float capsuleDelta(vector point, vector a, vector ab, const float radius);
  float mhcpLogoCylinder(vector point);


  template<int xInt, int yInt, int radiusInt>
  float capsuleDeltaCt(vector point, vector a) {
    const float abX = floatInt<xInt>::value;
    const float abY = floatInt<yInt>::value;
    const float radius = floatInt<radiusInt>::value;

    const vector ab(abX, abY);
    const float  abDotInverse = 1.0f / (abX * abX + abY * abY);

    vector ap = point - a;

    float  percentage = helper::clamp(ap.dotProduct(ab) * abDotInverse, 0.0f, 1.0f);
    vector close      = a + ab.multiplyConst(percentage);

    return (close - point).length() - radius;
  }


  template<int startXInt, int startYInt, int startZInt, int deltaXInt, int deltaYInt, int radiusInt>
  float capsuleCt(vector point) {
    const vector a(floatInt<startXInt>::value, floatInt<startYInt>::value, floatInt<startZInt>::value);
    const float abX    = floatInt<deltaXInt>::value;
    const float abY    = floatInt<deltaYInt>::value;
    const float radius = floatInt<radiusInt>::value;

    const vector ab(abX, abY);     // AB = B - START = DELTA
    const float  abDotInverse = 1.0f / (abX * abX + abY * abY);

    vector ap = point - a;

    float  percentage = helper::clamp(ap.dotProduct(ab) * abDotInverse, 0.0f, 1.0f);
    vector close      = ab.multiplyConst(percentage) + a;

    return (close - point).length() - radius;
  }



  template<int startXInt, int startYInt, int startZInt, int deltaXInt, int deltaYInt>
  float lineSquaredCt(vector point) {
    const vector a(floatInt<startXInt>::value, floatInt<startYInt>::value, floatInt<startZInt>::value);
    const float abX    = floatInt<deltaXInt>::value;
    const float abY    = floatInt<deltaYInt>::value;

    const vector ab(abX, abY);     // AB = B - START = DELTA
    const float  abDotInverse = 1.0f / (abX * abX + abY * abY);

    vector ap = point - a;

    float  percentage = helper::clamp(ap.dotProduct(ab) * abDotInverse, 0.0f, 1.0f);
    vector close      = ab.multiplyConst(percentage) + a;

    return (close - point).dotProduct();
  }


  template<int sizeXint, int sizeYint, bool quadrant1, bool quadrant7, bool quadrant9, bool quadrant3>
  float mhcpDodlyDood(vector point) {
    // Only C++20 is supporting float as a non-type template parameter, but I want this code to be C++17 compatible
    // so therefore this workaround where I pass 'int' but then do constexpr conversion to float
    // https://en.cppreference.com/w/cpp/language/template_parameters#Non-type_template_parameter
    constexpr float sizeX = floatInt<sizeXint>::value;
    constexpr float sizeY = floatInt<sizeYint>::value;

    const float  roundNess      = 0.25f; // By default all corners are rounded
    const vector smoothSize     = vector(sizeX - roundNess, sizeY - roundNess, 2.0f);

    const vector sharpSizeHalf  = vector(+sizeX / 2.0f, +sizeY / 2.0f, 2.0f);

    const vector cornerSame     = vector(+sizeX / 2.0f, +sizeY / 2.0f, 0.0f);
    const vector cornerOpposite = vector(+sizeX / 2.0f, -sizeY / 2.0f, 0.0f);

    // First calculating the whole box with smooth rounded corners
    float answer = box(point, smoothSize) - roundNess;

    // Able to make any of the 4 corners/quadrants sharp, the numbers are based on numpad location style
    if (quadrant1) answer = helper::minf(answer, box(point - cornerOpposite, sharpSizeHalf));
    if (quadrant7) answer = helper::minf(answer, box(point - cornerSame,     sharpSizeHalf));
    if (quadrant9) answer = helper::minf(answer, box(point + cornerOpposite, sharpSizeHalf));
    if (quadrant3) answer = helper::minf(answer, box(point + cornerSame,     sharpSizeHalf));

    return answer;
  }

};


#endif //RAYMARCHER_SIGNEDDISTANCE_H
