#ifndef _INCLUDE_FONTMANAGER_HPP_
#define _INCLUDE_FONTMANAGER_HPP_

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontManager {
  public:
    // FontManager();
    // ~FontManager();

    bool Init();

    TTF_Font* LoadFont(const char* filepath, int ptsize);

    bool AddFont(std::string key, TTF_Font* font);

    bool DrawTextImmediately(
      SDL_Renderer* renderer,
      std::string key,
      std::string content,
      int x,
      int y,
      SDL_Color color = { 0, 0, 0 }
    );

    SDL_Texture* CreateTextureFromText(
      SDL_Renderer* renderer,
      std::string key,
      std::string content,
      SDL_Color color = { 0, 0, 0 }
    );

    void FreeFont(std::string key);

    void Clear();

    void Quit();

  private:
    std::map<std::string, TTF_Font*> font_map;
};
#endif
