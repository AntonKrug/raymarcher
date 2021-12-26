//
// Created by AntonKrug on 26/12/21.
//

#ifndef RAYMARCHER_SAMPLER_H
#define RAYMARCHER_SAMPLER_H

#include <cfloat>
#include <tuple>

#include "config.h"

namespace Sampler {
  constexpr unsigned int pattern = 0;

  float vanDerCorput(unsigned int sampleIndex);
  float sobol2(unsigned int sampleIndex);
  std::tuple<float, float> vanDerCoruptSobol2(unsigned int sampleIndex);

  // https://stackoverflow.com/questions/19108345/c1y-c14-variable-template-specialization

  template <int lookupIndex>
  constexpr std::array<std::tuple<float, float>, config::maxSamples> populateSampleTable() {
    auto previousResult = populateSampleTable<lookupIndex + 1>();

    previousResult[lookupIndex] = Sampler::vanDerCoruptSobol2(lookupIndex);

    return previousResult;
  }


  template <>
  constexpr std::array<std::tuple<float, float>, config::maxSamples> populateSampleTable<config::maxSamples>() {
    return {};
  }


};


#endif //RAYMARCHER_SAMPLER_H
