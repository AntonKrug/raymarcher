//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_VECTOR_H
#define RAYMARCHER_VECTOR_H

#include <cfloat>

struct vector {
  float x, y, z;

  explicit vector(float init = 0.0f);
  vector(float xInit, float yInit, float zInit = 0.0f);

  vector operator+(vector second);
  void operator+=(vector second);
  vector operator-(vector second);
  vector operator*(vector second);

  vector operator+(float scalar);
  vector operator-(float scalar);
  vector operator*(float scalar);
  vector operator/(float scalar);

  vector multiply(float scalar);
  float dotProduct(vector second);
  float dotProduct();
  float squared();
  float length();
  vector normalize();

  vector nudgeX();
  vector nudgeY();
  vector nudgeZ();

};


#endif //RAYMARCHER_VECTOR_H
