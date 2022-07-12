#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"
#include "GameInfo.hpp"

const int UPDATE_PER_SECOND = 10;
const int DURATION_PER_UPDATE = 1000 / UPDATE_PER_SECOND;

int main(int argc, char *args[]) {

  // Init SDL

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Init SDL_ttf

  if (TTF_Init() != 0) {
    std::cout << "TTF_Init HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return 1;
  }

  if (!loadFont()) {
    std::cout << "TTF_OpenFont HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return 1;
  }

  // Init window

  SDL_Window* window = SDL_CreateWindow(
    "Conway's Game of Life",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    520,
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

  // Init game

  initCellsRandom();
  // printCells();

  // Main loop

  Uint32 last_update = 0;

  bool quit = false;

  SDL_StopTextInput(); // !important for unsing SDLK_p to pause

  while (!quit) {
    Uint64 loop_start = SDL_GetPerformanceCounter();

    // Handle events
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          {
            switch (event.key.keysym.sym) {
              case SDLK_ESCAPE:
                quit = true;
                break;
              case SDLK_p:
                pause = !pause;
                break;
              case SDLK_SPACE:
                pause = !pause;
                break;
              default:
                break;
            }
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          {
            switch (event.button.button) {
              case SDL_BUTTON_LEFT:
                {
                  onLeftMouseDown(&event.button);
                }
                break;
              default:
                break;
            }
          }
          break;
        case SDL_MOUSEBUTTONUP:
          {
            switch (event.button.button) {
              case SDL_BUTTON_LEFT:
                {
                  onLeftMouseUp(&event.button);
                }
                break;
              default:
                break;
            }
          }
          break;
        case SDL_MOUSEMOTION:
          onMouseMotion(&event.motion);
          break;
        default:
          break;
      }
    }

    // And update other game stuff

    if (!pause) {
      Uint32 current = SDL_GetTicks();
      if (current - last_update >= DURATION_PER_UPDATE) {
        updateCells();
        cell_generations++;
        last_update = current;
      }
    }

    // Erase the last frame
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw (Invisible yet!)

    renderCells(renderer);
    drawLines(renderer);
    drawHoverCell(renderer);
    drawSelectedCell(renderer);
    drawGameInfo(renderer);

    // Render (Visible now!)
    SDL_RenderPresent(renderer);

    // Calculate real fps
    float loop_ms = (SDL_GetPerformanceCounter() - loop_start) / (float)SDL_GetPerformanceFrequency();
    int fps = 1 / loop_ms;
    // std::cout << fps << "\n";
  }

  // Clean up and quit

  cleanupFont();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
