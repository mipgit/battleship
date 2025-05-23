#include "arena_view.h"

extern uint8_t *current_buffer;
extern uint8_t *arena_buffer;
extern unsigned int frame_size;
extern vbe_mode_info_t mode_info;

extern Sprite *ship1;
extern Sprite *ship2h;
extern Sprite *ship2v;
extern Sprite *ship3h;
extern Sprite *ship3v;
extern Sprite *ship4h;
extern Sprite *ship4v;
extern Sprite *double_grid;
extern Sprite *single_grid;
extern Sprite *player1;
extern Sprite *player1s;
extern Sprite *player2;
extern Sprite *player2s;

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
    draw_grid(&arena.player1_grid, 0);
  } else if (arena_phase == SETUP_PLAYER2 && current_player == PLAYER_2) {
    draw_grid(&arena.player2_grid, 0);
  
  } else if (arena_phase == READY_PHASE) {
    if (current_player == PLAYER_1) {
      draw_grid(&arena.player1_grid, 1);
      draw_grid(&arena.player2_grid, 1);
    } else if (current_player == PLAYER_2) {
      draw_grid(&arena.player2_grid, 1);
      draw_grid(&arena.player1_grid, 1);
    }  
  }

  draw_player(current_player);
}


void draw_grid(Grid *grid, bool hide_ships) {
    int hovered_row, hovered_col, hovered_ship_id;
    bool hovering = mouse_over_ship(grid, cursor_x, cursor_y, &hovered_row, &hovered_col, &hovered_ship_id);
  
  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(grid, i, j, &x, &y);
      draw_cell(grid, x, y, i, j, hovering ? hovered_ship_id : -1, hide_ships);
    }
  }
}



void draw_cell(Grid *grid, int x, int y, int cell_row, int cell_col, int hovered_ship_id, bool hide_ships) {

  Cell *cell = &grid->cells[cell_row][cell_col];

  //only draw ships at their starting position to avoid duplicates
  if ((cell->state == SHIP || cell->ship_id >= 0) && !hide_ships) {
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
  draw_rectangle(x, y, CELL_WIDTH, CELL_HEIGHT, YELLOW, current_buffer);
}


void draw_player(PlayerTurn player) {

  int player1_x = arena.player1_grid.sprite_x + GRID_WIDTH/2 - player1->width/2;
  int player2_x = arena.player2_grid.sprite_x + GRID_WIDTH/2 - player2->width/2;
  int player_y = arena.player1_grid.sprite_x + GRID_HEIGHT + 50;

  if (player == PLAYER_1) {
    draw_sprite(player1s, player1_x, player_y, current_buffer);
    draw_sprite(player2, player2_x, player_y, current_buffer);
  } else if (player == PLAYER_2) {
    draw_sprite(player2s, player2_x, player_y, current_buffer);
    draw_sprite(player1, player1_x, player_y, current_buffer);
  }
}

