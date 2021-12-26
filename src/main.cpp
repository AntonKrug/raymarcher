//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <iostream>

#include "config.h"
#include "sampler.h"

const auto sampleLookupTable = Sampler::populateSampleTable<0>();




int main(int argc, char ** argv) {
  bool keepLooping = true;

  sdl::setup();

  while (keepLooping) {
    sdl::update();

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        keepLooping = false;
        break;

    }

    sdl::render();
  }

  sdl::tearUp();

  return 0;
}