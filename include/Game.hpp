#include <iostream>
#include <time.h>

#include <SDL2/SDL.h>

const int ROWS = 48;
const int COLS = 64;
const int CELL_RENDER_SIZE = 10;

bool pause = false;

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

int selected_cell_row = -1;
int selected_cell_col = -1;

void onLeftMouseDown(SDL_MouseButtonEvent* p_eventbtn) {
  if (!p_eventbtn || !p_eventbtn->button) return;

  selected_cell_row = p_eventbtn->y / CELL_RENDER_SIZE;
  selected_cell_col = p_eventbtn->x / CELL_RENDER_SIZE;
}

void onLeftMouseUp(SDL_MouseButtonEvent* p_eventbtn) {
  if (!p_eventbtn || !p_eventbtn->button) return;

  int current_selected_cell_row = p_eventbtn->y / CELL_RENDER_SIZE;
  int current_selected_cell_col = p_eventbtn->x / CELL_RENDER_SIZE;

  // Change selected cell status:
  if (current_selected_cell_col == selected_cell_col
    && current_selected_cell_row == selected_cell_row
  ) {
    cells[selected_cell_row][selected_cell_col] = (int)!cells[selected_cell_row][selected_cell_col];
  }

  // reset, !important
  selected_cell_row = -1;
  selected_cell_col = -1;
}

int hover_cell_row = -1;
int hover_cell_col = -1;
void onMouseMotion(SDL_MouseMotionEvent* p_motion) {
  hover_cell_row = p_motion->y / CELL_RENDER_SIZE;
  hover_cell_col = p_motion->x / CELL_RENDER_SIZE;
}

SDL_Rect cell_rect;

void renderCells(SDL_Renderer* p_renderer) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      cell_rect.x = j * CELL_RENDER_SIZE;
      cell_rect.y = i * CELL_RENDER_SIZE;
      cell_rect.w = CELL_RENDER_SIZE;
      cell_rect.h = CELL_RENDER_SIZE;

      if (cells[i][j]) { // alive cell
        SDL_SetRenderDrawColor(p_renderer, 128, 0, 0, 255);
      } else { // dead cell
        SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);
      }

      SDL_RenderFillRect(p_renderer, &cell_rect);
    }
  }
}

void drawLines(SDL_Renderer* p_renderer) {
  SDL_SetRenderDrawColor(p_renderer, 196, 196, 196, 255);

  for (int row = 0; row < ROWS; ++row) {
    const int y = row * CELL_RENDER_SIZE;
    SDL_RenderDrawLine(p_renderer, 0, y, COLS * CELL_RENDER_SIZE, y);
  }

  for (int col = 0; col < COLS; ++col) {
    const int x = col * CELL_RENDER_SIZE;
    SDL_RenderDrawLine(p_renderer, x, 0, x, ROWS * CELL_RENDER_SIZE);
  }
}

void drawSelectedCell(SDL_Renderer* p_renderer) {
  if (selected_cell_col >= 0
    && selected_cell_col < COLS
    && selected_cell_row >= 0
    && selected_cell_row < ROWS
  ) {
    SDL_Rect rect;
    rect.x = selected_cell_col * CELL_RENDER_SIZE;
    rect.y = selected_cell_row * CELL_RENDER_SIZE;
    rect.w = CELL_RENDER_SIZE;
    rect.h = CELL_RENDER_SIZE;

    SDL_SetRenderDrawColor(p_renderer, 128, 0, 0, 255);
    SDL_RenderFillRect(p_renderer, &rect);
  }
}

void drawHoverCell(SDL_Renderer* p_renderer) {
  if (hover_cell_col >= 0
    && hover_cell_col < COLS
    && hover_cell_row >= 0
    && hover_cell_row < ROWS
  ) {
    SDL_Rect rect;
    rect.x = hover_cell_col * CELL_RENDER_SIZE;
    rect.y = hover_cell_row * CELL_RENDER_SIZE;
    rect.w = CELL_RENDER_SIZE;
    rect.h = CELL_RENDER_SIZE;

    SDL_SetRenderDrawColor(p_renderer, 212, 186, 191, 255);
    SDL_RenderFillRect(p_renderer, &rect);
  }
}
