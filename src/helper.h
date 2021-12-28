//
// Created by Fredy on 26/12/21.
//

#ifndef RAYMARCHER_HELPER_H
#define RAYMARCHER_HELPER_H


namespace helper {

  // For RISC-V baremetal + newlib target this has to be written in asm
  float min(float a, float b);
  float min3(float a, float b, float c);

  float max(float a, float b);
  float max3(float a, float b, float c);
  float min5(float a, float b, float c, float d, float e);

  float clamp(float a, float min, float max);

};


#endif //RAYMARCHER_HELPER_H
