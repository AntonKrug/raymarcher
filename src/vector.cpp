//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "vector.h"

#include <cmath>
#include "config.h"
#include "helper.h"


vector::vector(const float init): x(init), y(init), z(init) {
}

vector::vector(const float xInit, const float yInit, const float zInit): x(xInit), y(yInit), z(zInit) {
}


vector vector::operator+(const vector second) {
  return vector(x + second.x, y + second.y, z + second.z);
}


void vector::operator+=(const vector second) {
  x += second.x;
  y += second.y;
  z += second.z;
}


vector vector::operator-(const vector second) {
  return vector(x - second.x, y - second.y, z - second.z);
}


vector vector::operator+(const float scalar) {
  return vector(x + scalar, y + scalar, z + scalar);
}

vector vector::operator-(const float scalar) {
  return vector(x - scalar, y - scalar, z - scalar);
}


vector vector::operator*(const vector second) {
  return vector(x * second.x, y * second.y, z * second.z);
}


vector vector::operator*(const float scalar) {
  return vector(x * scalar, y * scalar, z * scalar);
}


vector vector::multiply(const float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return *this;
}


vector vector::operator/(const float scalar) {
  return vector(x / scalar, y / scalar, z / scalar);
}


float vector::dotProduct(const vector second) {
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

const vector vector::multiply(const vector second) const {
  return vector(x * second.x, y * second.y, z * second.z);
}

vector vector::multiplyConst(const float scalar) const {
  return vector(x * scalar, y * scalar, z * scalar);
}

vector vector::abs() const {
  return vector(fabs(x), fabs(y), fabs(z));
}

vector vector::max(float scalar) const {
  return vector(helper::max(x, scalar), helper::max(y, scalar), helper::max(z, scalar));
}

vector vector::min(float scalar) const {
  return vector(helper::min(x, scalar), helper::min(y, scalar), helper::min(z, scalar));
}

vector vector::maxInPlace(float scalar) {
  x = helper::max(x, scalar);
  y = helper::max(y, scalar);
  z = helper::max(z, scalar);

  return *this;
}
