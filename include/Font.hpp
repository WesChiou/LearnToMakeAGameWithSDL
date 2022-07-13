#ifndef _INCLUDE_FONT_HPP_
#define _INCLUDE_FONT_HPP_

#include <iostream>

#include <SDL2/SDL_ttf.h>

class Font {
  public:
    Font();
    ~Font();

    bool Init();
    bool OpenFont(const char* file, int ptsize);
    void CloseFont();
    void Cleanup();
    void Quit();

    TTF_Font* GetFont();

  private:
    TTF_Font* font;
};

Font::Font() {

}

Font::~Font() {

}

bool Font::Init() {
  if (TTF_Init() != 0) {
    std::cout << "TTF_Init HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }
  return true;
}

bool Font::OpenFont(const char* file, int ptsize) {
  font = TTF_OpenFont(file, ptsize);

  if (!font) {
    std::cout << "TTF_OpenFont HAS FAILED. ERROR: " << TTF_GetError() << std::endl;
    return false;
  }

  return true;
}

void Font::CloseFont() {
  TTF_CloseFont(font);
}

void Font::Cleanup() {
  TTF_CloseFont(font);
}

void Font::Quit() {
  TTF_Quit();
}

TTF_Font* Font::GetFont() {
  return font;
}

#endif
