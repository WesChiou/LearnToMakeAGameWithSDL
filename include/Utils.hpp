#ifndef _INCLUDE_UTILS_HPP_
#define _INCLUDE_UTILS_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Utils {
  bool DrawText(
    SDL_Renderer* renderer,
    const char* text,
    TTF_Font* font,
    int x,
    int y,
    SDL_Color color
  );
}

#endif
