//
// Created by Fredy on 26/12/21.
//

#include "helper.h"

// TODO: implement as folds + templates

helper::helper(float valueInit): value(valueInit) {
}


helper helper::operator<<(helper second) {
  value = minf2(value, second.value);
  return *this;
}

helper helper::operator>>(helper second) {
  value = maxf2(value, second.value);
  return *this;
}


// For RISC-V baremetal + newlib target this has to be written in asm
float helper::minf2(float a, float b) {
  return (a > b) ? b : a;
}


// For RISC-V baremetal + newlib target this has to be written in asm
float helper::maxf2(float a, float b) {
  return (a > b) ? a : b;
}


float helper::clamp(float a, float minValue, float maxValue) {
  return minf2(maxf2(a, minValue), maxValue);
}

