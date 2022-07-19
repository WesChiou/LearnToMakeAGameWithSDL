#ifndef _INCLUDE_EVENTS_HPP
#define _INCLUDE_EVENTS_HPP

#include <iostream>

#include <SDL2/SDL.h>

namespace Events {
  Uint32 CUSTOM_EVENT;

  bool RegisterCustomEvent() {
    CUSTOM_EVENT = SDL_RegisterEvents(1);

    if (CUSTOM_EVENT == ((Uint32) - 1)) {
      std::cout << "SDL_RegisterEvents HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
      return false;
    }

    return true;
  }

  enum CustomEventsCode {
    SHOW_MENU,
  };

  void TriggerCustomEvent(CustomEventsCode code, void* data1) {
    SDL_Event event;
    event.type = Events::CUSTOM_EVENT;
    event.user.code = code;
    event.user.data1 = data1;

    SDL_PushEvent(&event);
  }
}

#endif
