//
// Created by Fredy on 26/12/21.
//

#include "helper.h"

namespace helper {

  float static fminfast2(float a, float b) {
    return a > b ? b : a;
  }


  float static fmaxfast2(float a, float b) {
    return a > b ? a : b;
  }


  float static clamp(float a, float min, float max) {
    return fminfast2(fmaxfast2(a, min), max);
  }

}