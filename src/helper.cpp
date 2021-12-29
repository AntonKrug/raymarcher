//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include "helper.h"


helper::helper(float valueInit): value(valueInit) {
}


// Wrapper to be able to do 'min' call with a 'operator<<', so then it can be used in the folds
helper helper::operator<<(helper second) {
  value = minf2(value, second.value);
  return *this;
}


// Wrapper to be able to do 'max' call with a 'operator>>', so then it can be used in the folds
helper helper::operator>>(helper second) {
  value = maxf2(value, second.value);
  return *this;
}


// TODO: Detect RISC-V (RISC-V baremetal + newlib) target as this has to be written in asm
float helper::minf2(float a, float b) {
  return (a > b) ? b : a;
}


// TODO: Detect RISC-V (RISC-V baremetal + newlib) target as this has to be written in asm
float helper::maxf2(float a, float b) {
  return (a > b) ? a : b;
}


float helper::clamp(float a, float minValue, float maxValue) {
  return minf2(maxf2(a, minValue), maxValue);
}

