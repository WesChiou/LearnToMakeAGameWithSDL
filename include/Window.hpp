#ifndef _INCLUDE_WINDOW_HPP_
#define _INCLUDE_WINDOW_HPP_

#include <iostream>

#include <SDL2/SDL.h>

class Window {
  public:
    Window();
    ~Window();

    bool Init();
    void Cleanup();
    void Quit();

    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();

  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

Window::Window() {

}

Window::~Window() {

}

bool Window::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow(
    "Conway's Game of Life",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    520,
    0
  );

  if (!window) {
    std::cout << "SDL_CreateWindow HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    std::cout << "SDL_CreateRenderer HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Window::Cleanup() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}

void Window::Quit() {
  SDL_Quit();
}

SDL_Window* Window::GetWindow() {
  return window;
}

SDL_Renderer* Window::GetRenderer() {
  return renderer;
}

#endif
