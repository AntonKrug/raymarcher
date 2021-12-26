//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <iostream>

#include "config.h"
#include "outputSdl.h"
#include "rayMarcher.h"


int main(int argc, char ** argv) {
  bool keepLooping = true;
  int y = 0;

  outputSdl::setup();

  while (keepLooping) {
    outputSdl::update();

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        keepLooping = false;
        break;
    }

    if (y<config::height) {
      rayMarcher::renderLine(y);
      y++;
    }

    outputSdl::render();
  }

  outputSdl::tearUp();

  return 0;
}