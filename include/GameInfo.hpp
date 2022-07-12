#ifndef _INCLUDE_GAMEINFO_HPP_
#define _INCLUDE_GAMEINFO_HPP_

#include <iostream>

#include <SDL2/SDL_ttf.h>

#include "Game.hpp"

TTF_Font* font;

SDL_Color text_color = { 0, 0, 0 };

bool loadFont() {
  font = TTF_OpenFont("res/font/Roboto-Regular.ttf", 12);

  if (!font) return false;

  return true;
}

SDL_Surface* text_suface;
SDL_Texture* text_texture;

bool drawText(SDL_Renderer* p_renderer, const char* text, int x, int y) {
  if (!p_renderer) {
    return false;
  }

  text_suface = TTF_RenderUTF8_Solid(font, text, text_color);

  if (!text_suface) {
    return false;
  }

  text_texture = SDL_CreateTextureFromSurface(p_renderer, text_suface);

  SDL_Rect srcrect = { 0, 0, text_suface->w, text_suface->h };
  SDL_Rect dstrect = { x, y, text_suface->w, text_suface->h };

  SDL_RenderCopy(p_renderer, text_texture, &srcrect, &dstrect);

  SDL_FreeSurface(text_suface);
  SDL_DestroyTexture(text_texture);

  return true;
}

void drawGameInfo(SDL_Renderer* p_renderer) {
  char cellsCount[10];
  char generations[10];
  char time_in_second[10];

  std::string s;
  s += "Living Cells: ";
  s += itoa(countCells(), cellsCount, 10);
  s += "  Generations: ";
  s += itoa(cell_generations, generations, 10);
  s += "  Time: ";
  s += itoa(SDL_GetTicks() / 1000, time_in_second, 10);
  s += "s    Tips: Left Click to add or kill a cell;  Use SPACE or P to pause.";
  drawText(p_renderer, s.c_str(), 0, 484);

  drawText(p_renderer, "Conway's Game of Life | Program by Qiu Weishi | weishi@whut.edu.cn", 0, 500);
}

void cleanupFont() {
  TTF_CloseFont(font);
  SDL_FreeSurface(text_suface);
  SDL_DestroyTexture(text_texture);
}

#endif
