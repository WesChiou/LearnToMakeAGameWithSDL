#include <vector>
#include <iostream>
#include <string>

#include "Game.hpp"
#include "State.hpp"
#include "Utils.hpp"
#include "Events.hpp"
#include "StateMenu.hpp"

bool StateMenu::Init() {
  newgame_btn.rect = { menurect.x + 110, menurect.y + 90, 100, 20 };
  newgame_btn.text = "New Game";

  back_btn.rect = { menurect.x + 110, menurect.y + 130, 100, 20 };
  back_btn.text = "Back to Game";

  return true;
}

void StateMenu::HandleEvent(SDL_Event* e) {
  switch (e->type) {
    case SDL_KEYDOWN:
      {
        switch (e->key.keysym.sym) {
          case SDLK_ESCAPE:
            Events::TriggerCustomEvent(Events::EXIT_MENU, this);
            break;
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      {
        switch (e->button.button) {
          case SDL_BUTTON_LEFT:
            OnLeftMouseDown(&e->button);
            break;
          default:
            break;
        }
      }
      break;
    default:
      break;
  }
}

void StateMenu::Update() {

}

void StateMenu::Draw(Game* game) {
  SDL_Renderer* renderer = game->GetRenderer();
  TTF_Font* font = game->GetFont();

  // Draw menu box
  SDL_SetRenderDrawColor(renderer, 172, 196, 208, 255);
  SDL_RenderFillRect(renderer, &menurect);
  SDL_SetRenderDrawColor(renderer, 16, 32, 48, 255);
  SDL_RenderDrawRect(renderer, &menurect);

  // Draw buttons
  SDL_SetRenderDrawColor(renderer, 0x36, 0x4F, 0x6F, 0xFF);
  SDL_Color color = { 0xFF, 0xFF, 0xFF };

  SDL_RenderFillRect(renderer, &back_btn.rect);
  Utils::DrawText(renderer, back_btn.text.c_str(), font, back_btn.rect.x, back_btn.rect.y, color);

  SDL_RenderFillRect(renderer, &newgame_btn.rect);
  Utils::DrawText(renderer, newgame_btn.text.c_str(), font, newgame_btn.rect.x, newgame_btn.rect.y, color);
}

void StateMenu::OnLeftMouseDown(SDL_MouseButtonEvent* p_eventbtn) {
  if (!p_eventbtn) return;

  SDL_Point mouse = { p_eventbtn->x, p_eventbtn->y };

  if (SDL_PointInRect(&mouse, &back_btn.rect)) {
    Events::TriggerCustomEvent(Events::EXIT_MENU, this);
    return;
  }

  if (SDL_PointInRect(&mouse, &newgame_btn.rect)) {
    Events::TriggerCustomEvent(Events::NEW_GAME, this);
    return;
  }
}

void StateMenu::Cleanup() {

}
