#ifndef _INCLUDE_CONWAYSGAMEOFLIFE_HPP_
#define _INCLUDE_CONWAYSGAMEOFLIFE_HPP_

#include <iostream>
#include <time.h>

#include <SDL2/SDL.h>

#include "Utils.hpp"

const int MAX_ROWS = 1000;
const int MAX_COLS = 1000;
const int MAX_CELL_SIZE = 50;

struct Position {
  int row;
  int col;
};

class ConwaysGameOfLife {
  public:
    ConwaysGameOfLife();
    // ConwaysGameOfLife(int rows, int cols, int cellsize);
    ~ConwaysGameOfLife() { };

    void InitCellsRandomly();

    void Update();

    void Draw(SDL_Renderer* renderer, TTF_Font* font);

    void HandleEvents();

    bool IsRunning();

    int LivingCells();

  private:
    bool pause = false;
    bool running = true;
    Uint32 lastupdate = 0;

    int rows = 48;
    int cols = 64;
    int cellsize = 10;
    int generations = 0;
    int generation_per_second = 10;
    bool cells[MAX_ROWS][MAX_COLS] = { false };

    Position selected_cell = { -1, -1 };
    Position hovered_cell = { -1, -1 };

    void NextGeneration();
    void OnMouseMotion(SDL_MouseMotionEvent* p_motion);
    void OnLeftMouseDown(SDL_MouseButtonEvent* p_eventbtn);
    void OnLeftMouseUp(SDL_MouseButtonEvent* p_eventbtn);

    bool IsValidCellPos(Position pos);
};

ConwaysGameOfLife::ConwaysGameOfLife() {
  InitCellsRandomly();
};

// ConwaysGameOfLife::ConwaysGameOfLife(int p_rows, int p_cols, int p_cellsize) {
//   rows = p_rows > 0 && p_rows <= MAX_ROWS ? p_rows : 48;
//   cols = p_cols > 0 && p_cols <= MAX_COLS ? p_cols : 64;
//   cellsize = p_cellsize > 0 && p_cellsize <= MAX_CELL_SIZE ? p_cellsize : 10;
// }

void ConwaysGameOfLife::InitCellsRandomly() {
  srand(time(0));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells[i][j] = (bool)(rand() % 2);
    }
  }
}

void ConwaysGameOfLife::Update() {
  if (!pause) {
    Uint32 current = SDL_GetTicks();
    const Uint32 per_generation_ms = 1000 / generation_per_second;
    if (current - lastupdate >= per_generation_ms) {
      lastupdate = current;

      NextGeneration();
      generations++;
    }
  }
}

void ConwaysGameOfLife::NextGeneration() {
  // Get next generation cells
  int next_generation[rows][cols] = { 0 };
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // Count nearbys
      int nearbys = 0;
      for (int row = i - 1; row <= i + 1; row++) {
        for (int col = j - 1; col <= j + 1; col++) {
          if (row >= 0
            && row < rows
            && col >= 0
            && col < cols
            && !(row == i && col == j) // [i][j] is itself
          ) {
            nearbys += (int)cells[row][col];
          }
        }
      }
      // Conway's game of life rules:
      const bool current = cells[i][j];
      if (current && nearbys < 2) {
        next_generation[i][j] = 0;
      } else if (current && (nearbys == 2 || nearbys == 3)) {
        next_generation[i][j] = current; // or: next_generation[i][j] = true;
      } else if (current && nearbys > 3) {
        next_generation[i][j] = 0;
      } else if (!current && nearbys == 3) {
        next_generation[i][j] = 1;
      }
    }
  }

  // Update
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells[i][j] = next_generation[i][j];
    }
  }
}

void ConwaysGameOfLife::Draw(SDL_Renderer* renderer, TTF_Font* font) {
  // Draw cells
  SDL_Rect dstrect;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      dstrect = { j * cellsize, i * cellsize, cellsize, cellsize };
      if (cells[i][j]) { // Living cell
        SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
      } else { // Dead cell
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      }
      SDL_RenderFillRect(renderer, &dstrect);
    }
  }

  // Draw some nice lines
  SDL_SetRenderDrawColor(renderer, 196, 196, 196, 255);
  for (int r = 0; r <= rows; ++r) {
    const int y = r * cellsize;
    SDL_RenderDrawLine(renderer, 0, y, cols * cellsize, y);
  }
  for (int l = 0; l <= cols; ++l) {
    const int x = l * cellsize;
    SDL_RenderDrawLine(renderer, x, 0, x, rows * cellsize);
  }

  // Draw hovered cell
  if (IsValidCellPos(hovered_cell)) {
    dstrect = {
      hovered_cell.col * cellsize,
      hovered_cell.row * cellsize,
      cellsize,
      cellsize
    };
    SDL_SetRenderDrawColor(renderer, 212, 186, 191, 255);
    SDL_RenderFillRect(renderer, &dstrect);
  }

  // Draw selected cell
  if (IsValidCellPos(selected_cell)) {
    dstrect = {
      selected_cell.col * cellsize,
      selected_cell.row * cellsize,
      cellsize,
      cellsize
    };
    SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
    SDL_RenderFillRect(renderer, &dstrect);
  }

  // Draw game info
  char count_s[10];
  char generation_s[10];
  char time_s[10];

  std::string s;
  s += "Living Cells: ";
  s += itoa(LivingCells(), count_s, 10);
  s += "  Generations: ";
  s += itoa(generations, generation_s, 10);
  s += "  Time: ";
  s += itoa(SDL_GetTicks() / 1000, time_s, 10);
  s += "s  Tips: Left Click to add or kill a cell;  Use SPACE or P to pause.";
  SDL_Color color = { 0, 0, 0 };
  Utils::DrawText(renderer, s.c_str(), font, 0, 484, color);

  // Draw copyright
  Utils::DrawText(renderer, "Conway's Game of Life | Program by Qiu Weishi", font, 0, 500, color);
}

void ConwaysGameOfLife::HandleEvents() {
  SDL_StopTextInput(); // !important for unsing SDLK_p to pause
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
        {
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              running = false;
              break;
            case SDLK_p:
              pause = !pause;
              break;
            case SDLK_SPACE:
              pause = !pause;
              break;
            default:
              break;
          }
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        {
          switch (event.button.button) {
            case SDL_BUTTON_LEFT:
              {
                OnLeftMouseDown(&event.button);
              }
              break;
            default:
              break;
          }
        }
        break;
      case SDL_MOUSEBUTTONUP:
        {
          switch (event.button.button) {
            case SDL_BUTTON_LEFT:
              {
                OnLeftMouseUp(&event.button);
              }
              break;
            default:
              break;
          }
        }
        break;
      case SDL_MOUSEMOTION:
        OnMouseMotion(&event.motion);
        break;
      default:
        break;
    }
  }
}

bool ConwaysGameOfLife::IsRunning() {
  return running;
}

int ConwaysGameOfLife::LivingCells() {
  int count = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      count += (int)cells[i][j];
    }
  }
  return count;
}

void ConwaysGameOfLife::OnMouseMotion(SDL_MouseMotionEvent* p_motion) {
  if (!p_motion) return;
  hovered_cell.col = p_motion->x / cellsize;
  hovered_cell.row = p_motion->y / cellsize;
}

void ConwaysGameOfLife::OnLeftMouseDown(SDL_MouseButtonEvent* p_eventbtn) {
  if (!p_eventbtn) return;
  selected_cell.col = p_eventbtn->x / cellsize;
  selected_cell.row = p_eventbtn->y / cellsize;
}

void ConwaysGameOfLife::OnLeftMouseUp(SDL_MouseButtonEvent* p_eventbtn) {
  if (!p_eventbtn) return;

  Position current = { p_eventbtn->y / cellsize, p_eventbtn->x / cellsize };
  if (current.col == selected_cell.col
    && current.row == selected_cell.row
  ) {
    // Kill or live current selected:
    cells[current.row][current.col] = !cells[current.row][current.col];
  }

  // Reset selected cell to -1, -1
  selected_cell = { -1, -1 };
}

bool ConwaysGameOfLife::IsValidCellPos(Position pos) {
  if (pos.row >= 0 && pos.row < rows && pos.col >= 0 && pos.col < cols) {
    return true;
  }
  return false;
}

#endif
