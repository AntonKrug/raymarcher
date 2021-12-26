//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_SDL_H
#define RAYMARCHER_SDL_H

#include <SDL2/SDL.h>

#include "config.h"

namespace Sdl {
  Uint32 pixels[config::width * config::height];

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;

  void setup();
  void update();
  void render();
  void tearUp();

}


#endif //RAYMARCHER_SDL_H
