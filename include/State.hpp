#ifndef _INCLUDE_STATE_HPP_
#define _INCLUDE_STATE_HPP_

#include "SDL2/SDL.h"

class Game;

class State {
  public:
    // State();
    // ~State();
    virtual bool Init() = 0;
    virtual void HandleEvent(SDL_Event* e) = 0;
    virtual void Update() = 0;
    virtual void Draw(Game* game) = 0;
    virtual void Cleanup() = 0;

    // getters
    bool IsPause() { return pause; };
    bool IsInvisible() { return invisible; };
    bool IsSleep() { return sleep; };

  protected:
    bool pause = false; // Update() or not
    bool invisible = false; // Draw() or not
    bool sleep = false; // HandleEvent() or not
};

#endif
