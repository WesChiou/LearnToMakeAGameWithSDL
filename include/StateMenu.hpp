#ifndef _INCLUDE_STATEMENU_HPP_
#define _INCLUDE_STATEMENU_HPP_

#include <string>

#include "Game.hpp"
#include "State.hpp"

struct Button {
  SDL_Rect rect = { 0, 0, 0, 0 };
  std::string text = "";
};

class StateMenu: public State {
  public:
    // StateMenu();
    // ~StateMenu();

    bool Init();
    void HandleEvent(SDL_Event* e);
    void Update();
    void Draw(Game* game);
    void Cleanup();

    void OnLeftMouseDown(SDL_MouseButtonEvent* p_eventbtn);

  private:
    SDL_Rect menurect = { 160, 120, 320, 240 };
    Button back_btn;
    Button newgame_btn;
};

#endif
