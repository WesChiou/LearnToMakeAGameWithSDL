#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *args[]) {

  // Init SDL

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Init window

  SDL_Window* window = SDL_CreateWindow(
    "SDL Start",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    0
  );

  if (!window) {
    std::cout << "SDL_CreateWindow HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Init renderer

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    std::cout << "SDL_CreateRenderer HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Main loop

  bool quit = false;

  while (!quit) {
    // Handle events
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
        default:
          break;
      }
    }

    // And update other game stuff
    //

    // Erase the last frame
    SDL_RenderClear(renderer);

    // Draw (Invisible yet!)
    //

    // Render (Visible now!)
    SDL_RenderPresent(renderer);
  }

  // Clean up and quit

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
