#include <iostream>
#include <SDL2/SDL.h>

namespace rm {
  constexpr int width  = 512;
  constexpr int height = 480;

  constexpr int displayWidth = width * 2;
  constexpr int displayHeight = height * 2;
}


namespace sdl {
  Uint32 pixels[rm::width * rm::height];

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;

  void setup() {
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
      std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(
        "Ray Marcher",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        rm::displayWidth,
        rm::displayHeight,
        0       // flags
    );

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, rm::width, rm::height);

    memset(pixels, 0xff, rm::width * rm::height * sizeof(Uint32));
  }

  void update() {
    SDL_UpdateTexture(texture, NULL, pixels, rm::width * sizeof(Uint32));
  }

  void render() {
    const SDL_Rect dest = {.x = 0, .y = 0, .w = rm::displayWidth, .h = rm::displayHeight};
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