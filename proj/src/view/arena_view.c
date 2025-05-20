#include "arena_view.h"

extern uint8_t *current_buffer;
extern Sprite *grid;
extern Sprite *ship1;
extern Sprite *ship2h;
extern Sprite *ship2v;
extern Sprite *ship3h;
extern Sprite *ship3v;
extern Sprite *ship4v;
extern Sprite *grid;

extern Arena arena;


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
  fill_screen(PINK, current_buffer);
  draw_sprite(grid, 0,0, current_buffer);
  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(i, j, &x, &y);
      draw_cell(x, y, i, j, &arena.player1_grid.cells[i][j]); 
    }
  }
}


void draw_cell(int x, int y, int cell_row, int cell_col, Cell *cell) {
  // Only draw ships at their starting position to avoid duplicates
  if (cell->state == SHIP && cell->ship_id >= 0) {
    Ship *ship = &arena.player1_grid.ships[cell->ship_id];
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
  vg_draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, RED);
}

void draw_miss_marker(int x, int y) {
  vg_draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, YELLOW);
}


