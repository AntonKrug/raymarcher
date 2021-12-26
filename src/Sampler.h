//
// Created by AntonKrug on 26/12/21.
//

#ifndef RAYMARCHER_SAMPLER_H
#define RAYMARCHER_SAMPLER_H

#include <cfloat>
#include <tuple>

class Sampler {
private:
  unsigned int pattern;

  float vanDerCorput(unsigned int sampleIndex);

  float sobol2(unsigned int sampleIndex);

  std::tuple<float, float> vanDerCoruptSobol2(unsigned int sampleIndex);

public:
  Sampler();

  explicit Sampler(unsigned int patternInit);

};


#endif //RAYMARCHER_SAMPLER_H
