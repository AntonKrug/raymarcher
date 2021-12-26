//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_VECTOR_H
#define RAYMARCHER_VECTOR_H

#include <cfloat>

struct Vector {
  float x, y, z;

  explicit Vector(float init = 0.0f);
  Vector(float xInit, float yInit, float zInit = 0.0f);

  Vector operator+(Vector second);
  void operator+=(Vector second);
  Vector operator-(Vector second);
  Vector operator*(Vector second);
  Vector operator*(float scalar);
  Vector operator/(float scalar);

  Vector multiply(float scalar);
  float dotProduct(Vector second);
  float dotProduct();
  float squared();
  float length();
  Vector normalized();

  Vector nudgeX();
  Vector nudgeY();
  Vector nudgeZ();

};


#endif //RAYMARCHER_VECTOR_H
