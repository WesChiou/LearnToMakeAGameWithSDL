#ifndef _INCLUDE_TEXTUREMANAGER_HPP_
#define _INCLUDE_TEXTUREMANAGER_HPP_

#include <map>
#include <string>

#include <SDL2/SDL.h>

class TextureManager {
  public:
    // TextureManager();
    // ~TextureManager();

    bool LoadTexture(SDL_Renderer* renderer, const char* filepath);

    bool DrawTexture(
      SDL_Renderer* renderer,
      std::string filepath,
      SDL_Rect* srcrect,
      SDL_Rect* dstrect,
      double scale
    );

    void FreeTexture(std::string filepath);

  private:
    std::map<std::string, SDL_Texture*> texture_map;
};

#endif
