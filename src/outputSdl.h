//
// Created by anton.krug@gmail.com on 26/12/21.
// License: MIT
//

#ifndef RAYMARCHER_OUTPUTSDL_H
#define RAYMARCHER_OUTPUTSDL_H

#include <SDL2/SDL.h>

#include "config.h"

namespace outputSdl {
  extern Uint32 pixels[config::width * config::height];

  extern SDL_Window *window;
  extern SDL_Renderer *renderer;
  extern SDL_Texture *texture;

  void setup();
  void update();
  void render();
  void tearUp();

}


#endif //RAYMARCHER_OUTPUTSDL_H
