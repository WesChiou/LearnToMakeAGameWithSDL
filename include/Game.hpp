#ifndef _INCLUDE_GAME_HPP_
#define _INCLUDE_GAME_HPP_

#include <iostream>
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "State.hpp"

class Game {
  public:
    // Game();
    // ~Game();

    bool Init();
    void HandleEvents();
    void Update();
    void Draw();
    void Cleanup();
    void Quit();
    bool IsRunning();

    void AddState(State* state);
    // void ChangeState();
    // void PushState();
    // void PopState();

    // getters
    SDL_Window* GetWindow() { return window; };
    SDL_Renderer* GetRenderer() { return renderer; };
    TTF_Font* GetFont() { return font; };

    int fps = 0;

  private:
    bool running = true;

    std::vector<State*> states;

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
};

bool Game::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() != 0) {
    std::cout << "TTF_Init HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }

  font = TTF_OpenFont("res/font/Roboto-Regular.ttf", 12);

  if (!font) {
    std::cout << "TTF_OpenFont HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow(
    "Conway's Game of Life",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    520,
    0
  );

  if (!window) {
    std::cout << "SDL_CreateWindow HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (!renderer) {
    std::cout << "SDL_CreateRenderer HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Game::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      Quit();
      return;
    }

    for (auto state: states) {
      if (!state->IsSleep()) {
        state->HandleEvent(&e);
      }
    }
  }
}

void Game::Update() {
  for (auto state: states) {
    if (!state->IsPause()) {
      state->Update();
    }
  }
}

void Game::Draw() {
  // Erase the last frame
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (auto state: states) {
    if (!state->IsInvisible()) {
      state->Draw(this);
    }
  }

  SDL_RenderPresent(renderer);
}

void Game::Cleanup() {
  // Cleanup all states
  for (auto state: states) {
    state->Cleanup();
  }
  states.clear();

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void Game::Quit() {
  running = false;
}

bool Game::IsRunning() {
  return running;
}

void Game::AddState(State* state) {
  state->Init();
  states.push_back(state);
}

#endif