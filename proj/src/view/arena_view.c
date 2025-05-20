#include "arena_view.h"

extern uint8_t *current_buffer;
extern Sprite *grid;
extern Sprite *ship1;
extern Sprite *ship2h;
extern Sprite *ship2v;
extern Sprite *ship3h;
extern Sprite *ship3v;
extern Sprite *ship4v;
extern Sprite *double_grid;
extern Sprite *single_grid;

extern Arena arena;

extern int cursor_x;
extern int cursor_y;


/*
void draw_arena() {
  fill_screen(PINK, current_buffer);
  draw_sprite(grid, 0,0, current_buffer);
  draw_sprite(ship1, 31, 31, current_buffer);
  draw_sprite(ship1, 31 + 33*4 + 4, 31 + 33*1 + 1, current_buffer);
  draw_sprite(ship1, 31 + 33*7 + 7, 31 + 33*5 + 5, current_buffer);
  draw_sprite(ship2h, 269, 303, current_buffer); //31 + 33*7 + 7 , 31 + 33*8 + 8
  draw_sprite(ship2v, 133, 133, current_buffer);  //31(início) + 33*3(quadrados) + 3(linhas)
  draw_sprite(ship3h, 235, 99, current_buffer); //31 + 33*6 + 6 , 31 + 33*2 + 2
  draw_sprite(ship3v, 201, 235, current_buffer); //31 + 33*5 + 5 , 31 + 33*6 + 6
  draw_sprite(ship4v, 65, 235, current_buffer); //31 + 33*1 + 1, 31 + 33*6 + 6
}
*/


void draw_arena() {
  fill_screen(YELLOW, current_buffer);
  draw_grid(&arena.player1_grid);
  draw_grid(&arena.player2_grid);
}


void draw_grid(Grid *grid) {
  draw_sprite(single_grid, grid->sprite_x, grid->sprite_y, current_buffer);

  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(grid, i, j, &x, &y);
      draw_cell(grid, x, y, i, j);
    }
  }
}



void draw_cell(Grid *grid, int x, int y, int cell_row, int cell_col) {

  Cell *cell = &grid->cells[cell_row][cell_col];

  if (cursor_x >= x && cursor_x < x + CELL_WIDTH &&
      cursor_y >= y && cursor_y < y + CELL_HEIGHT) {
    draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, HOVER_COLOR, current_buffer);
  }

  // Only draw ships at their starting position to avoid duplicates
  if (cell->state == SHIP && cell->ship_id >= 0) {
    Ship *ship = &grid->ships[cell->ship_id];
    if (ship->start_row == cell_row && ship->start_col == cell_col) {
        draw_ship_sprite(x, y, ship->type, ship->orientation);
    }
  }
  else if (cell->state == HIT) {
    draw_hit_marker(x, y);
  }
  else if (cell->state == MISS) {
    draw_miss_marker(x, y);
  }
}




void draw_ship_sprite(int x, int y, ShipType type, int orientation) {
  switch (type) {
    case SHIP_1:
      draw_sprite(ship1, x, y, current_buffer);
      break;
    case SHIP_2:
      if (orientation == 0)
        draw_sprite(ship2h, x, y, current_buffer);
      else
        draw_sprite(ship2v, x, y, current_buffer);
      break;
    case SHIP_3:
      if (orientation == 0)
        draw_sprite(ship3h, x, y, current_buffer);
      else
        draw_sprite(ship3v, x, y, current_buffer);
      break;
    case SHIP_4:
      draw_sprite(ship4v, x, y, current_buffer);
      break;
    default:
      break;
  }
}



void draw_hit_marker(int x, int y) {
  draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, RED, current_buffer);
}

void draw_miss_marker(int x, int y) {
  draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, YELLOW, current_buffer);
}


