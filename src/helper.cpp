//
// Created by Fredy on 26/12/21.
//

#include "helper.h"

namespace helper {

  // TODO: implement as folds + templates

  float min(float a, float b) {
    return (a > b) ? b : a;
  }

  float min3(float a, float b, float c) {
    return min(min(a, b), c);
  }

  float max(float a, float b) {
    return (a > b) ? a : b;
  }

  float max3(float a, float b, float c) {
    return max(max(a, b), c);
  }

  float clamp(float a, float min, float max) {
    return min(max(a, min), max);
  }

}