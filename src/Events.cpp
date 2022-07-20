#include <iostream>

#include <SDL2/SDL.h>

#include "Events.hpp"

Uint32 Events::CUSTOM_EVENT;

bool Events::RegisterCustomEvent() {
  CUSTOM_EVENT = SDL_RegisterEvents(1);

  if (CUSTOM_EVENT == ((Uint32) - 1)) {
    std::cout << "SDL_RegisterEvents HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Events::TriggerCustomEvent(CustomEventsCode code, void* data1) {
  SDL_Event event;
  event.type = Events::CUSTOM_EVENT;
  event.user.code = code;
  event.user.data1 = data1;

  SDL_PushEvent(&event);
}
