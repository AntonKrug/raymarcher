//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <iostream>

#include "config.h"
#include "sampler.h"
#include "Sdl.h"

const auto sampleLookupTable = Sampler::populateSampleTable<0>();

int main(int argc, char ** argv) {
  bool keepLooping = true;

  Sdl::setup();

  while (keepLooping) {
    Sdl::update();

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        keepLooping = false;
        break;

    }

    Sdl::render();
  }

  Sdl::tearUp();

  return 0;
}