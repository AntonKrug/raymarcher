//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

// Taken from my previous project: https://github.com/truhlikfredy/raytracer/blob/master/src/render/sampler.cpp

#include "sampler.h"


constexpr float sampler::vanDerCorput(unsigned int sampleIndex) {
  sampleIndex = (sampleIndex << 16) | (sampleIndex >> 16);
  sampleIndex = ((sampleIndex & 0x00ff00ff) << 8) | ((sampleIndex & 0xff00ff00) >> 8);
  sampleIndex = ((sampleIndex & 0x0f0f0f0f) << 4) | ((sampleIndex & 0xf0f0f0f0) >> 4);
  sampleIndex = ((sampleIndex & 0x33333333) << 2) | ((sampleIndex & 0xcccccccc) >> 2);
  sampleIndex = ((sampleIndex & 0x55555555) << 1) | ((sampleIndex & 0xaaaaaaaa) >> 1);
  sampleIndex ^= pattern;
  return (float)sampleIndex / (float)0x100000000LL;
}


constexpr float sampler::sobol2(unsigned int sampleIndex) {
  int localPattern = pattern;
  for (unsigned int v = 1 << 31; sampleIndex != 0; sampleIndex >>= 1, v ^= v >> 1)
    if (sampleIndex & 0x1) localPattern ^= v;
  return (float)localPattern / (float)0x100000000LL;
}


constexpr std::tuple<float, float> sampler::vanDerCoruptSobol2(unsigned int sampleIndex) {
  return {
      vanDerCorput(sampleIndex),
      sobol2(sampleIndex)
  };
}


const std::array<std::tuple<float, float>, config::maxSamples> sampler::lutBoth         = sampler::populateSampleTable<0>();
const std::array<float, config::maxSamples>                    sampler::lutVanDerCorput = sampler::generatorVanDerCoruptLut<config::maxSamples>;
const std::array<float, config::maxSamples>                    sampler::lutSobol2       = sampler::generatorSobol2Lut<config::maxSamples>;

