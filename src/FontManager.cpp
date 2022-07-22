#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "FontManager.hpp"

bool FontManager::Init() {
  if (TTF_Init() != 0) {
    std::cout << "TTF_Init HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }
  return true;
}

TTF_Font* FontManager::LoadFont(const char* filepath, int ptsize) {
  TTF_Font* font = TTF_OpenFont(filepath, ptsize);

  if (!font) {
    std::cout << "TTF_OpenFont HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return nullptr;
  }

  return font;
}

bool FontManager::AddFont(std::string key, TTF_Font* font) {
  // TODO: validation
  font_map[key] = font;
  return true;
}

bool FontManager::DrawTextImmediately(
  SDL_Renderer* renderer,
  std::string key,
  std::string content,
  int x,
  int y,
  SDL_Color color
) {
  SDL_Surface* surface = TTF_RenderUTF8_Solid(font_map[key], content.c_str(), color);

  if (!surface) {
    std::cout << "DrawTextImmediately | TTF_RenderUTF8_Solid HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    std::cout << "DrawTextImmediately | SDL_CreateTextureFromSurface HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Rect srcrect = { 0, 0, surface->w, surface->h };
  SDL_Rect dstrect = { x, y, surface->w, surface->h };

  if (SDL_RenderCopy(renderer, texture, &srcrect, &dstrect) != 0) {
    std::cout << "DrawTextImmediately | SDL_RenderCopy HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_DestroyTexture(texture);

  return true;
}

SDL_Texture* FontManager::CreateTextureFromText(
  SDL_Renderer* renderer,
  std::string key,
  std::string content,
  SDL_Color color
) {
  SDL_Surface* surface = TTF_RenderUTF8_Solid(font_map[key], content.c_str(), color);

  if (!surface) {
    std::cout << "CreateTextureFromText | TTF_RenderUTF8_Solid HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    std::cout << "CreateTextureFromText | SDL_CreateTextureFromSurface HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}

void FontManager::FreeFont(std::string key) {
  TTF_CloseFont(font_map[key]);
  font_map.erase(key);
}

void FontManager::Clear() {
  for(auto pair: font_map) {
    TTF_CloseFont(pair.second);
  }
  font_map.clear();
}

void FontManager::Quit() {
  Clear();
  TTF_Quit();
}
