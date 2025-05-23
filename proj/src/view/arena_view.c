#include "arena_view.h"

extern uint8_t *current_buffer;
extern uint8_t *arena_buffer;
extern unsigned int frame_size;
extern vbe_mode_info_t mode_info;

extern Sprite *grid;
extern Sprite *ship1;
extern Sprite *ship2h;
extern Sprite *ship2v;
extern Sprite *ship3h;
extern Sprite *ship3v;
extern Sprite *ship4h;
extern Sprite *ship4v;
extern Sprite *double_grid;
extern Sprite *single_grid;

extern Arena arena;
extern ArenaPhase arena_phase;
extern PlayerTurn current_player;

extern int cursor_x;
extern int cursor_y;



void draw_arena_background(uint8_t *buffer) {
  fill_screen(BETTER_BLUE, buffer);
  draw_sprite(single_grid, arena.player1_grid.sprite_x, arena.player1_grid.sprite_y, buffer);
  draw_sprite(single_grid, arena.player2_grid.sprite_x, arena.player2_grid.sprite_y, buffer);
}



void draw_arena() {
  memcpy(current_buffer, arena_buffer, frame_size);

  if (arena_phase == SETUP_PLAYER1 && current_player == PLAYER_1) {
    draw_grid(&arena.player1_grid);
  } else if (arena_phase == SETUP_PLAYER2 && current_player == PLAYER_2) {
    draw_grid(&arena.player2_grid);
  
  } else if (arena_phase == READY_PHASE) {
    draw_grid(&arena.player1_grid);
    draw_grid(&arena.player2_grid);
  }
}


void draw_grid(Grid *grid) {
    int hovered_row, hovered_col, hovered_ship_id;
    bool hovering = mouse_over_ship(grid, cursor_x, cursor_y, &hovered_row, &hovered_col, &hovered_ship_id);
  
  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(grid, i, j, &x, &y);
      draw_cell(grid, x, y, i, j, hovering ? hovered_ship_id : -1);
    }
  }
}



void draw_cell(Grid *grid, int x, int y, int cell_row, int cell_col, int hovered_ship_id) {

  Cell *cell = &grid->cells[cell_row][cell_col];

  //only draw ships at their starting position to avoid duplicates
  if (cell->state == SHIP || cell->ship_id >= 0) {
    Ship *ship = &grid->ships[cell->ship_id];
    if (ship->start_row == cell_row && ship->start_col == cell_col) {
        draw_ship_sprite(x, y, ship->type, ship->orientation);
    }
  }

  if (cursor_x >= x && cursor_x < x + CELL_WIDTH &&
      cursor_y >= y && cursor_y < y + CELL_HEIGHT) {
    draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, HOVER_COLOR, current_buffer);
  }


  //only show ship hover in SETUP_PHASE
  if ((arena_phase == SETUP_PLAYER1 || arena_phase == SETUP_PLAYER2) && cell->ship_id == hovered_ship_id && hovered_ship_id >= 0) {
      draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, SHIP_HOVER_COLOR, current_buffer);
  }

  //always show cell hover
  else if (cursor_x >= x && cursor_x < x + CELL_WIDTH &&
           cursor_y >= y && cursor_y < y + CELL_HEIGHT) {
      draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, HOVER_COLOR, current_buffer);
  }

  
  if (cell->state == HIT) {
    draw_hit_marker(x, y);
  }
  if (cell->state == MISS) {
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
      if (orientation == 0)
        draw_sprite(ship4h, x, y, current_buffer);
      else
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
  draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, PURPLE, current_buffer);
}


