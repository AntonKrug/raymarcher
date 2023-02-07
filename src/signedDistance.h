//
// Created by anton.krug@gmail.com on 27/12/21.
// License: MIT
//


#ifndef RAYMARCHER_SIGNEDDISTANCE_H
#define RAYMARCHER_SIGNEDDISTANCE_H

#include "vector.h"
#include "helper.h"

namespace signedDistance {

  float box(vector point, vector size);
  float capsule(vector point, vector a, vector b, const float radius);
  float capsuleDelta(vector point, vector a, vector ab, const float radius);
  float mhcpLogoCylinder(vector point);


  template<float x, float y, float z, float radius>
  float sphereCt(const vector& point) {
    const vector center(x,  y, z);

    return (point - center).length() - radius;
  }


  template<float abX, float abY, float radius>
  float capsuleDeltaCt(const vector& point, const vector& a) {
    constexpr float  abDotInverse = 1.0f / (abX * abX + abY * abY);
    const vector ab(abX, abY);

    vector ap = point - a;

    float  percentage = helper::clamp(ab.dotProduct(ap) * abDotInverse, 0.0f, 1.0f);
    vector close      = a + ab.multiplyConst(percentage);

    return (close - point).length() - radius;
  }


  template<float startX, float startY, float startZ, float deltaX, float deltaY, float radius>
  inline __attribute__((always_inline)) float capsuleCt(const vector& point) {
    constexpr float  abDotInverse = 1.0f / (deltaX * deltaX + deltaY * deltaY);
    const vector a(startX, startY, startZ);
    const vector ab(deltaX, deltaY);     // AB = B - START = DELTA

    vector ap = point - a;

    float  percentage = helper::clamp(ab.dotProduct(ap) * abDotInverse, 0.0f, 1.0f);
    vector close      = ab.multiplyConst(percentage) + a;

    return (close - point).length() - radius;
  }


  template<float startX, float startY, float startZ, float deltaX, float deltaY>
  inline __attribute__((always_inline)) float lineSquaredCt(const vector& point) {
    // Is similar to capsuleCt, but will not calculate the thickness of the line to make it into a capsule.
    // So it's not really a true signed distance function (as the solid body is infinitely small)
    // After this line call a radius and its square root needs to be calculated to make it into real
    // signed distance function, such as capsuleCt. The benefit to do it this way is that bunch of lines with
    // the same thickness can be calculated in bulk and then thickness applied to them in one operation.
    constexpr float  abDotInverse = 1.0f / (deltaX * deltaX + deltaY * deltaY);
    const vector a(startX, startY, startZ);
    const vector ab(deltaX, deltaY);     // AB = B - START = DELTA

    vector ap = point - a;

    float  percentage = helper::clamp(ab.dotProduct(ap) * abDotInverse, 0.0f, 1.0f);
    vector close      = ab.multiplyConst(percentage) + a;

    return (close - point).dotProduct();
  }


  template<float sizeX, float sizeY, bool quadrant1, bool quadrant7, bool quadrant9, bool quadrant3>
  inline __attribute__((always_inline)) float mhcpDodlyDood(const vector& point) {
    // This is a rectangle with some corners being rounded/smooth and some right angle (depending on the template arguments)
    // This solid is used inside the MCHP logo 3 times
    const float  roundNess      = 0.25f; // By default, all corners are rounded
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
