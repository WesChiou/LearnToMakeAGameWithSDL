#include <iostream>
#include <time.h>

#include <SDL2/SDL.h>

const int ROWS = 48;
const int COLS = 64;
const int CELL_RENDER_SIZE = 10;

int cells[ROWS][COLS] = {0};

// For debug
void printCells() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      std::cout << cells[i][j] << " ";
    }
    std::cout << "\n";
  }
}

void initCellsRandom() {
  srand(time(0));

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      cells[i][j] = rand() % 2;
    }
  }
}

void updateCells() {
  int new_cells[ROWS][COLS] = {0};

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      const int current = cells[i][j];

      // count nearbys
      int nearbys = 0;
      for (int row = i - 1; row <= i + 1; row++) {
        for (int col = j - 1; col <= j + 1; col++) {
          if (row >= 0
            && row < ROWS
            && col >= 0
            && col < COLS
            && !(row == i && col == j) // [i][j] is itself
          ) {
            nearbys += cells[row][col];
          }
        }
      }

      if (current && nearbys < 2) {
        new_cells[i][j] = 0;
      } else if (current && (nearbys == 2 || nearbys == 3)) {
        new_cells[i][j] = current; // or: new_cells[i][j] = 1;
      } else if (current && nearbys > 3) {
        new_cells[i][j] = 0;
      } else if (!current && nearbys == 3) {
        new_cells[i][j] = 1;
      }
    }
  }

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      cells[i][j] = new_cells[i][j];
    }
  }
}


SDL_Rect cell_rect;

void renderCells(SDL_Renderer* p_renderer) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      cell_rect.x = j * CELL_RENDER_SIZE;
      cell_rect.y = i * CELL_RENDER_SIZE;
      cell_rect.w = CELL_RENDER_SIZE;
      cell_rect.h = CELL_RENDER_SIZE;

      if (cells[i][j]) { // alive cell, fill by white
        SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);
      } else { // dead cell, fill by dark
        SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
      }

      SDL_RenderFillRect(p_renderer, &cell_rect);
    }
  }
}
