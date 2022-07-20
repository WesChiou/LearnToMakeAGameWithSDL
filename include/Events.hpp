#ifndef _INCLUDE_EVENTS_HPP_
#define _INCLUDE_EVENTS_HPP_

#include <SDL2/SDL.h>

namespace Events {
  extern Uint32 CUSTOM_EVENT;

  enum CustomEventsCode {
    SHOW_MENU,
    EXIT_MENU,
    NEW_GAME,
  };

  bool RegisterCustomEvent();

  void TriggerCustomEvent(CustomEventsCode code, void* data1);
}

#endif
