//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <iostream>
#include <chrono>

#include "config.h"
#include "outputSdl.h"
#include "rayMarcher.h"
#include "scenes/all.h"


int main(int argc, char ** argv) {
  bool keepLooping = true;
  int y = 0;

  outputSdl::setup();

  auto tsStart = std::chrono::high_resolution_clock::now();

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
      rayMarcher<mchp>::renderLine(y);
      outputSdl::render();
      y++;

      if (config::height == y) {
        auto tsEnd = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tsEnd - tsStart);
        std::cout << "Time to complete: " << duration.count() << "ms" << std::endl;
      }
    } else {
      SDL_Delay(100);
    }

  }

  outputSdl::tearUp();

  return 0;
}