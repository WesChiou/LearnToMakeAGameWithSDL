#include <iostream>

#include <SDL2/SDL.h>

#include "Window.hpp"
#include "Font.hpp"
#include "ConwaysGameOfLife.hpp"

int main(int argc, char *args[]) {
  // Init window and renderer
  Window window = Window();
  if (!window.Init()) {
    return 1;
  }
  SDL_Renderer* renderer = window.GetRenderer();

  // Init SDL_ttf
  Font font = Font();
  if (!font.Init()) {
    return 1;
  }
  if (!font.OpenFont("res/font/Roboto-Regular.ttf", 12)) {
    return 1;
  }

  // Init game
  ConwaysGameOfLife game = ConwaysGameOfLife();

  // Main loop
  while (game.IsRunning()) {
    Uint64 loop_start = SDL_GetPerformanceCounter();

    game.HandleEvents();
    game.Update();

    // Erase the last frame
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw (Invisible yet!)
    game.Draw(renderer, font.GetFont());

    // Render (Visible now!)
    SDL_RenderPresent(renderer);

    // Calculate real fps
    float loop_ms = (SDL_GetPerformanceCounter() - loop_start) / (float)SDL_GetPerformanceFrequency();
    int fps = 1 / loop_ms;
    // std::cout << fps << "\n";
  }

  // Clean up and quit
  font.Cleanup();
  font.Quit();
  window.Cleanup();
  window.Quit();

  return 0;
}
