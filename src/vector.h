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

  vector operator+(vector second) const;
  vector operator-(vector second) const;
  vector operator*(vector second) const;

  void operator+=(vector second);

  vector operator+(float scalar) const;
  vector operator-(float scalar) const;
  vector operator*(float scalar) const;
  vector operator/(float scalar) const;

  vector multiply(vector second) const;
  vector multiply(float scalar);
  vector multiplyConst(float scalar) const;
  float dotProduct(vector second) const;
  float dotProduct() const;
  float squared() const;
  float length() const;
  vector normalize();
  vector abs() const;
  vector max(float scalar) const;
  vector min(float scalar) const;
  vector maxInPlace(float scalar);

  vector nudgeX() const;
  vector nudgeY() const;
  vector nudgeZ() const;

};


#endif //RAYMARCHER_VECTOR_H
