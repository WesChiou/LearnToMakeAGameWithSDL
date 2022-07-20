#ifndef _INCLUDE_WORLDSTATE_HPP_
#define _INCLUDE_WORLDSTATE_HPP_

#include <SDL2/SDL.h>

#include "State.hpp"
#include "Game.hpp"

const int MAX_ROWS = 1000;
const int MAX_COLS = 1000;
const int MAX_CELL_SIZE = 50;

struct Position {
  int row;
  int col;
};

class StateBoard: public State {
  public:
    // StateBoard();
    // ~StateBoard();
    bool Init();
    void HandleEvent(SDL_Event* e);
    void Update();
    void Draw(Game* game);
    void Cleanup();

    int LivingCells();

  private:
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

#endif
