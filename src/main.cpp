#include <iostream>

#include <SDL2/SDL.h>

#include "Game.hpp"
#include "StateBoard.hpp"

int main(int argc, char *args[]) {
  Game game;

  if (!game.Init()) {
    return 1;
  }

  StateBoard board;
  game.PushState(&board);

  while (game.IsRunning()) {
    Uint64 loop_start = SDL_GetPerformanceCounter();

    game.HandleEvents();
    game.Update();
    game.Draw();

    // Calculate real fps
    float loop_ms = (SDL_GetPerformanceCounter() - loop_start) / (float)SDL_GetPerformanceFrequency();
    game.fps = 1 / loop_ms;
  }

  game.Cleanup();

  return 0;
}
