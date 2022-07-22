#ifndef _INCLUDE_TEXTUREMANAGER_HPP_
#define _INCLUDE_TEXTUREMANAGER_HPP_

#include <map>
#include <string>

#include <SDL2/SDL.h>

class TextureManager {
  public:
    // TextureManager();
    // ~TextureManager();

    bool Init();

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filepath);

    bool AddTexture(std::string key, SDL_Texture* texture);

    bool DrawTexture(
      SDL_Renderer* renderer,
      std::string key,
      SDL_Rect* srcrect,
      SDL_Rect* dstrect,
      double scale = 1
    );

    void FreeTexture(std::string key);

    void Clear();

    void Quit();

  private:
    std::map<std::string, SDL_Texture*> texture_map;
};

#endif
