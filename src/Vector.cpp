//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "Vector.h"

#include <cmath>
#include "config.h"


Vector::Vector(float init): x(init), y(init), z(init) {
}

Vector::Vector(float xInit, float yInit, float zInit): x(xInit), y(yInit), z(zInit) {
}


Vector Vector::operator+(Vector second) {
  return Vector(x + second.x, y + second.y, z + second.z);
}


void Vector::operator+=(Vector second) {
  x += second.x;
  y += second.y;
  z += second.z;
}


Vector Vector::operator-(Vector second) {
  return Vector(x - second.x, y - second.y, z - second.z);
}


Vector Vector::operator-(float scalar) {
  return Vector(x - scalar, y - scalar, z - scalar);
}


Vector Vector::operator*(Vector second) {
  return Vector(x * second.x, y * second.y, z * second.z);
}


Vector Vector::operator*(float scalar) {
  return Vector(x * scalar, y * scalar, z * scalar);
}


Vector Vector::multiply(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return *this;
}


Vector Vector::operator/(float scalar) {
  return Vector(x / scalar, y / scalar, z / scalar);
}


float Vector::dotProduct(Vector second) {
  return x * second.x + y * second.y + z * second.z;
}


float Vector::dotProduct() {
  return (*this).dotProduct(*this);
}


float Vector::squared() {
  return dotProduct();
}


float Vector::length() {
  return sqrtf(squared());
}


Vector Vector::normalized() {
  return *this / length();
}


Vector Vector::nudgeX() {
  return Vector(x + config::nudgeOffset, y, z);
}


Vector Vector::nudgeY() {
  return Vector(x, y + config::nudgeOffset, z);
}


Vector Vector::nudgeZ() {
  return Vector(x, y, z + config::nudgeOffset);
}

