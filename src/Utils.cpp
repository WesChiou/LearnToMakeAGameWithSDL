#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Utils.hpp"

bool Utils::DrawText(
  SDL_Renderer* renderer,
  const char* text,
  TTF_Font* font,
  int x,
  int y,
  SDL_Color color
) {
  SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, color);

  if (!surface) {
    std::cout << "DrawText | TTF_RenderUTF8_Solid HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (!texture) {
    std::cout << "DrawText | SDL_CreateTextureFromSurface HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Rect srcrect = { 0, 0, surface->w, surface->h };
  SDL_Rect dstrect = { x, y, surface->w, surface->h };

  if (SDL_RenderCopy(renderer, texture, &srcrect, &dstrect) != 0) {
    std::cout << "DrawText | SDL_RenderCopy HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return true;
}
