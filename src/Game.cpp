#include <iostream>
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "State.hpp"
#include "StateMenu.hpp"
#include "StateBoard.hpp"
#include "Events.hpp"

#include "Game.hpp"

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

  if (!Events::RegisterCustomEvent()) {
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
    if (e.type == SDL_QUIT) { // Quit
      Quit();
    } else if (e.type == Events::CUSTOM_EVENT) { // User custom events
      switch (e.user.code) {
        case Events::SHOW_MENU:
          {
            State* from = (State*)e.user.data1;
            from->sleep = true;
            from->pause = true;

            StateMenu* menu = new StateMenu();
            PushState(menu);
          }
          break;
        case Events::EXIT_MENU:
          {
            // Exit menu
            PopState();
            // Awake board
            State* board = states.back();
            board->sleep = false;
            board->pause = false;
          }
          break;
        case Events::NEW_GAME:
          {
            // Exit menu
            PopState();
            // Exit current game
            PopState();
            // New game
            StateBoard* board = new StateBoard();
            PushState(board);
          }
          break;
        default:
          break;
      }
    } else { // Dispatch events to each awake state:
      for (auto state: states) {
        if (!state->sleep) {
          state->HandleEvent(&e);
        }
      }
    }
  }
}

void Game::Update() {
  for (auto state: states) {
    if (!state->pause) {
      state->Update();
    }
  }
}

void Game::Draw() {
  // Erase the last frame
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (auto state: states) {
    if (!state->invisible) {
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

void Game::PushState(State* state) {
  states.push_back(state);
  state->Init();
}

void Game::PopState() {
  if (states.empty()) return;

  states.back()->Cleanup();
  states.pop_back();
}
