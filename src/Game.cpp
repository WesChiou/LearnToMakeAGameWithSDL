#include <iostream>
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "State.hpp"
#include "StateMenu.hpp"
#include "StateBoard.hpp"
#include "events.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "Game.hpp"

bool Game::Init() {
  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  // Init window
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

  // Init renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    std::cout << "SDL_CreateRenderer HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  // Init TextureManager
  texture_manager = new TextureManager();
  if (!texture_manager->Init()) {
    return false;
  }

  // Init FontManager and load a font
  font_manager = new FontManager();
  if (!font_manager->Init()) {
    return false;
  }
  TTF_Font* font_tmp = font_manager->LoadFont("res/font/Roboto-Regular.ttf", 12);
  if (!font_tmp) {
    return false;
  }
  font_manager->AddFont("Roboto-Regular", font_tmp);

  if (!events::RegisterCustomEvent()) {
    return false;
  }

  return true;
}

void Game::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) { // Quit
      Quit();
    } else if (e.type == events::CUSTOM_EVENT) { // User custom events
      switch (e.user.code) {
        case events::SHOW_MENU:
          {
            State* from = (State*)e.user.data1;
            from->sleep = true;
            from->pause = true;

            StateMenu* menu = new StateMenu();
            PushState(menu);
          }
          break;
        case events::EXIT_MENU:
          {
            // Exit menu
            PopState();
            // Awake board
            State* board = states.back();
            board->sleep = false;
            board->pause = false;
          }
          break;
        case events::NEW_GAME:
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

  texture_manager->Quit();
  font_manager->Quit();

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

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
