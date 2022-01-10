//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_SAMPLER_H
#define RAYMARCHER_SAMPLER_H

#include <cfloat>
#include <tuple>

#include "config.h"
#include "cppTrickery/lut.h"


namespace sampler {
  constexpr unsigned pattern = 1236789;

  extern const std::array<std::tuple<float, float>, config::maxSamples> lutBoth;
  extern const std::array<float, config::maxSamples> lutVanDerCorput;
  extern const std::array<float, config::maxSamples> lutSobol2;

  constexpr float vanDerCorput(unsigned int sampleIndex);
  constexpr float sobol2(unsigned int sampleIndex);
  constexpr std::tuple<float, float> vanDerCoruptSobol2(unsigned int sampleIndex);

  
  // https://stackoverflow.com/questions/19108345/c1y-c14-variable-template-specialization

  template <unsigned int lookupIndex>
  constexpr std::array<std::tuple<float, float>, config::maxSamples> populateSampleTable() {
    auto previousResult = populateSampleTable<lookupIndex + 1>();

    previousResult[lookupIndex] = vanDerCoruptSobol2(lookupIndex);

    return previousResult;
  }


  template<std::size_t size>
  inline constexpr auto generatorVanDerCoruptLut = lut<size>([](std::size_t sampleIndex){
    return sampler::vanDerCorput(sampleIndex);
  });


  template<std::size_t size>
  inline constexpr auto generatorSobol2Lut = lut<size>([](std::size_t sampleIndex){
    return sampler::sobol2(sampleIndex);
  });


  template <>
  constexpr std::array<std::tuple<float, float>, config::maxSamples> populateSampleTable<config::maxSamples>() {
    return {};
  }


};


#endif //RAYMARCHER_SAMPLER_H
