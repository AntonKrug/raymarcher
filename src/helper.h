//
// Created by Fredy on 26/12/21.
//

#ifndef RAYMARCHER_HELPER_H
#define RAYMARCHER_HELPER_H


namespace helper {

  // For RISC-V baremetal + newlib target this has to be written in asm
  float fminfast2(float a, float b);
  float fminfast3(float a, float b, float c);

  float fmaxfast2(float a, float b);
  float fmaxfast3(float a, float b, float c);

  float clamp(float a, float min, float max);

};


#endif //RAYMARCHER_HELPER_H
