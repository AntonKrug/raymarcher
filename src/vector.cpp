//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "vector.h"

#include <cmath>
#include "config.h"


vector::vector(float init): x(init), y(init), z(init) {
}

vector::vector(float xInit, float yInit, float zInit): x(xInit), y(yInit), z(zInit) {
}


vector vector::operator+(vector second) {
  return vector(x + second.x, y + second.y, z + second.z);
}


void vector::operator+=(vector second) {
  x += second.x;
  y += second.y;
  z += second.z;
}


vector vector::operator-(vector second) {
  return vector(x - second.x, y - second.y, z - second.z);
}


vector vector::operator+(float scalar) {
  return vector(x + scalar, y + scalar, z + scalar);
}

vector vector::operator-(float scalar) {
  return vector(x - scalar, y - scalar, z - scalar);
}


vector vector::operator*(vector second) {
  return vector(x * second.x, y * second.y, z * second.z);
}


vector vector::operator*(float scalar) {
  return vector(x * scalar, y * scalar, z * scalar);
}


vector vector::multiply(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return *this;
}


vector vector::operator/(float scalar) {
  return vector(x / scalar, y / scalar, z / scalar);
}


float vector::dotProduct(vector second) {
  return x * second.x + y * second.y + z * second.z;
}


float vector::dotProduct() {
  return (*this).dotProduct(*this);
}


float vector::squared() {
  return dotProduct();
}


float vector::length() {
  return sqrtf(squared());
}


vector vector::normalize() {
  return *this / length();
}


vector vector::nudgeX() {
  return vector(x + config::nudgeOffset, y, z);
}


vector vector::nudgeY() {
  return vector(x, y + config::nudgeOffset, z);
}


vector vector::nudgeZ() {
  return vector(x, y, z + config::nudgeOffset);
}

