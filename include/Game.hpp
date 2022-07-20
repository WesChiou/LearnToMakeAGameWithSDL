#ifndef _INCLUDE_GAME_HPP_
#define _INCLUDE_GAME_HPP_

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

    void PushState(State* state);
    void PopState();

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

#endif
