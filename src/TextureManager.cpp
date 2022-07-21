#include <iostream>

#include <SDL2/SDL_image.h>

#include "TextureManager.hpp"

bool TextureManager::LoadTexture(SDL_Renderer* renderer, const char* filepath) {
  SDL_Surface* surface = IMG_Load(filepath);

  if (!surface) {
    std::cout << "IMG_Load HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    std::cout << "SDL_CreateTextureFromSurface HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  texture_map[filepath] = texture;

  return true;
}

bool TextureManager::DrawTexture(
  SDL_Renderer* renderer,
  std::string filepath,
  SDL_Rect* srcrect,
  SDL_Rect* dstrect,
  double scale
) {
  if (!texture_map[filepath]) {
    // Auto load texture.
    if (!LoadTexture(renderer, filepath.c_str())) {
      return false;
    }
  }
  if (SDL_RenderCopy(renderer, texture_map[filepath], srcrect, dstrect) != 0) {
    std::cout << "SDL_RenderCopy HAS FAILURE. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void TextureManager::FreeTexture(std::string filepath) {
  SDL_DestroyTexture(texture_map[filepath]);
  texture_map.erase(filepath);
}

void TextureManager::ClearTexture() {
  for(auto pair: texture_map) {
    SDL_DestroyTexture(pair.second);
  }
  texture_map.clear();
}
