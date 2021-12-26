//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#include <iostream>
#include "Sdl.h"

namespace sdl {

  void setup() {
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
      std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(
        "Ray Marcher",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config::displayWidth,
        config::displayHeight,
        0       // flags
    );

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, config::width, config::height);

    memset(pixels, 0xff, config::width * config::height * sizeof(Uint32));
  }

  void update() {
    SDL_UpdateTexture(texture, NULL, pixels, config::width * sizeof(Uint32));
  }

  void render() {
    const SDL_Rect dest = {.x = 0, .y = 0, .w = config::displayWidth, .h = config::displayHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_RenderPresent(renderer);
  }

  void tearUp() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

}
