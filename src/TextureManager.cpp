#include <iostream>

#include <SDL2/SDL_image.h>

#include "TextureManager.hpp"

bool TextureManager::Init() {
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    std::cout << "IMG_Init HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* filepath) {
  SDL_Surface* surface = IMG_Load(filepath);

  if (!surface) {
    std::cout << "IMG_Load HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    std::cout << "SDL_CreateTextureFromSurface HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}

bool TextureManager::AddTexture(std::string key, SDL_Texture* texture) {
  // TODO: validation
  texture_map[key] = texture;
  return true;
}

bool TextureManager::DrawTexture(
  SDL_Renderer* renderer,
  std::string key,
  SDL_Rect* srcrect,
  SDL_Rect* dstrect,
  double scale
) {
  // TODO: scale
  if (SDL_RenderCopy(renderer, texture_map[key], srcrect, dstrect) != 0) {
    std::cout << "DrawTexture HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void TextureManager::FreeTexture(std::string key) {
  SDL_DestroyTexture(texture_map[key]);
  texture_map.erase(key);
}

void TextureManager::Clear() {
  for(auto pair: texture_map) {
    SDL_DestroyTexture(pair.second);
  }
  texture_map.clear();
}

void TextureManager::Quit() {
  Clear();
  IMG_Quit();
}
