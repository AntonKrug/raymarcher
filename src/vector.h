//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_VECTOR_H
#define RAYMARCHER_VECTOR_H

#include <cfloat>

struct vector {
  float x, y, z;

  explicit vector(const float init = 0.0f);
  vector(const float xInit, const float yInit, const float zInit = 0.0f);

  vector operator+(const vector second);
  void operator+=(const vector second);
  vector operator-(const vector second);
  vector operator*(const vector second);

  vector operator+(const float scalar);
  vector operator-(const float scalar);
  vector operator*(const float scalar);
  vector operator/(const float scalar);

  const vector multiply(const vector second) const;
  vector multiply(const float scalar);
  vector multiplyConst(const float scalar) const;
  float dotProduct(const vector second);
  float dotProduct();
  float squared();
  float length();
  vector normalize();

  vector nudgeX();
  vector nudgeY();
  vector nudgeZ();

};


#endif //RAYMARCHER_VECTOR_H
