#include "arena.h"

extern vbe_mode_info_t mode_info;
extern struct packet mouse_packet; 
extern int cursor_x, cursor_y;
extern uint8_t *current_buffer;
uint8_t *arena_buffer;
extern unsigned int frame_size;
extern uint8_t scancode;

Arena arena;
ArenaPhase arena_phase = SETUP_PLAYER1;
PlayerTurn current_player = PLAYER_1;
DragState drag_state = {0, -1, 0, 0, 0, 0};
extern GameMode game_mode;


#define MAX_BOMBS_PER_TURN 5
int bombs_remaining = MAX_BOMBS_PER_TURN;



void arena_main_loop() { 
  draw_arena();
  draw_cursor(current_buffer);
  swap_buffers();
}



void set_arena_buffer() {
  if (arena_buffer == NULL) {
    arena_buffer = (uint8_t *) malloc(frame_size);
  }
}



void init_arena() {

  arena_phase = SETUP_PLAYER1;
  current_player = PLAYER_1;

  //initialize grids
  init_grid(&arena.player1_grid, 10, 40);
  init_grid(&arena.player2_grid, 410, 40);

  //draw background
  set_arena_buffer();
  draw_arena_background(arena_buffer);

  //setup ships
  setup_ships(&arena.player1_grid);
  if (game_mode == MULTI_PLAYER) setup_ships(&arena.player2_grid);
  else if (game_mode == SINGLE_PLAYER) {
    setup_pc_ships(&arena.player2_grid);
  }

}


void init_grid(Grid *grid, int sprite_x, int sprite_y) {

  grid->sprite_x = sprite_x;
  grid->sprite_y = sprite_y;
  grid->x = sprite_x + 31; 
  grid->y = sprite_y + 31; 

  grid->ships_remaining = NUM_SHIPS;


  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      grid->cells[i][j].state = EMPTY;
      grid->cells[i][j].ship_id = -1;
    }
  }

  for (int i = 0; i < NUM_SHIPS; i++) {
    grid->ships[i].type = NO_SHIP;
    grid->ships[i].size = 0;
    grid->ships[i].orientation = 0;
    grid->ships[i].start_row = -1;
    grid->ships[i].start_col = -1;
    grid->ships[i].status = ALIVE;
  }
}





void arena_keyboard_handler() {
  switch (scancode) {
    case R_KEY:
      if (arena_phase == SETUP_PLAYER1 && current_player == PLAYER_1) {
        current_player = PLAYER_2;
        arena_phase = SETUP_PLAYER2;
      } else if (arena_phase == SETUP_PLAYER2 && current_player == PLAYER_2) {
        current_player = PLAYER_1;
        arena_phase = READY_PHASE;
      }
      break;
    default:
      break;
  }
}



void arena_mouse_handler() {
  static bool prev_lb = false;
  bool curr_lb = mouse_packet.lb;

  if (arena_phase == SETUP_PLAYER1 && current_player == PLAYER_1) {
    setup_phase(curr_lb, prev_lb, &arena.player1_grid);
  } else if (arena_phase == SETUP_PLAYER2 && current_player == PLAYER_2) {
    setup_phase(curr_lb, prev_lb, &arena.player2_grid);
  } else if (arena_phase == READY_PHASE) {
    battle_phase(curr_lb, prev_lb);
  }

  prev_lb = curr_lb;
}



//used in ready/battle phase
void handle_mouse_click(Grid *grid, int mouse_x, int mouse_y) {
  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(grid, i, j, &x, &y);
      if (mouse_x >= x && mouse_x < x + CELL_WIDTH &&
          mouse_y >= y && mouse_y < y + CELL_HEIGHT) {
        
        Cell *cell = &grid->cells[i][j];
        
        if (cell->state == SHIP) {
          cell->state = HIT;
          printf("Hit!\n");

          if (is_ship_sunk(grid, cell->ship_id)) {
            grid->ships[cell->ship_id].status = SUNK;
            grid->ships_remaining--;
            printf("Ship sunk!\n");
            printf("Ships remaining: %d\n", grid->ships_remaining);

            //check if any player has won
            if (grid->ships_remaining == 0) {
              set_state(GAME_OVER);
            }
          }

        } else if (cell->state == EMPTY) {
          cell->state = MISS;
          printf("Miss!\n");
        }
        
        bombs_remaining--;
        return;
      }
    }
  }
}



/* READY PHASE: Bombing */
void battle_phase(bool curr_lb, bool prev_lb) {
  if (bombs_remaining > 0) { //check player still has bombsg
    if (curr_lb && !prev_lb) {
      if (current_player == PLAYER_1) {
        handle_mouse_click(&arena.player2_grid, cursor_x, cursor_y);
      } else if (current_player == PLAYER_2) {
        handle_mouse_click(&arena.player1_grid, cursor_x, cursor_y);
      }
    }
  } else {
    if (current_player == PLAYER_1) {
      current_player = PLAYER_2;
    } else if (current_player == PLAYER_2) {
      current_player = PLAYER_1;
    }
    bombs_remaining = MAX_BOMBS_PER_TURN; //reset bombs for the new turn
  }
}




/* SETUP PHASE: Drag and drop ships */
void setup_phase(bool curr_lb, bool prev_lb, Grid *grid) {
  if (curr_lb && !prev_lb) {
    int row, col, ship_id;
    if (mouse_over_ship(grid, cursor_x, cursor_y, &row, &col, &ship_id)) {
      drag_state.dragging = true;
      drag_state.origin_row = row;
      drag_state.origin_col = col;
      drag_state.ship_id = ship_id;
      drag_state.orientation = grid->ships[ship_id].orientation;
      drag_state.active_grid = grid;
    }
  }

  //on mouse release, drop ship if dragging
  if (!curr_lb && prev_lb && drag_state.dragging) {
    int drop_row, drop_col;
    //we check if the mouse is over a cell
    if (mouse_over_cell(grid, cursor_x, cursor_y, &drop_row, &drop_col) &&
        can_place_ship(grid, drop_row, drop_col,
                       grid->ships[drag_state.ship_id].size,
                       drag_state.orientation,
                       drag_state.ship_id)) {
      move_ship(grid, drag_state.ship_id, drop_row, drop_col, drag_state.orientation);
    
    //if the ship cannot be placed, revert to original position    
    } else {
      move_ship(grid, drag_state.ship_id, drag_state.origin_row, drag_state.origin_col, drag_state.orientation);
    }
    
    drag_state.dragging = false;
    drag_state.active_grid = NULL;
  }
}




//we check if the mouse is over a ship
bool mouse_over_ship(Grid *grid, int mouse_x, int mouse_y, int *row, int *col, int *ship_id) {
  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(grid, i, j, &x, &y);
      if (mouse_x >= x && mouse_x < x + CELL_WIDTH &&
        mouse_y >= y && mouse_y < y + CELL_HEIGHT &&
        grid->cells[i][j].state == SHIP) {
        *row = i;
        *col = j;
        *ship_id = grid->cells[i][j].ship_id;
        return true;
      }
    }
  }
  return false;
}

//we check if the mouse is over a grid cell
bool mouse_over_cell(Grid *grid, int mouse_x, int mouse_y, int *row, int *col) {
  for (int i = 0; i < GRID_ROWS; i++) {
    for (int j = 0; j < GRID_COLS; j++) {
      int x, y;
      cell_to_pixel(grid, i, j, &x, &y);
      if (mouse_x >= x && mouse_x < x + CELL_WIDTH &&
        mouse_y >= y && mouse_y < y + CELL_HEIGHT) {
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}





void move_ship(Grid *grid, int ship_id, int new_row, int new_col, int orientation) {
    //get ship info
    Ship *ship = &grid->ships[ship_id];
    int size = ship->size;
    int old_row = ship->start_row;
    int old_col = ship->start_col;
    int old_orientation = ship->orientation;

    //we remove ship from old position
    for (int i = 0; i < size; i++) {
        int row = (old_orientation == 0) ? old_row : old_row + i;
        int col = (old_orientation == 0) ? old_col + i : old_col;
        grid->cells[row][col].state = EMPTY;
        grid->cells[row][col].ship_id = -1;
    }

    //we try to place at new position
    if (can_place_ship(grid, new_row, new_col, size, orientation, ship_id)) {
        //place ship at new position
        ship->start_row = new_row;
        ship->start_col = new_col;
        ship->orientation = orientation;
        for (int i = 0; i < size; i++) {
            int row = (orientation == 0) ? new_row : new_row + i;
            int col = (orientation == 0) ? new_col + i : new_col;
            grid->cells[row][col].state = SHIP;
            grid->cells[row][col].ship_id = ship_id;
        }
    } else {
        //if invalid, restore to old position
        for (int i = 0; i < size; i++) {
            int row = (old_orientation == 0) ? old_row : old_row + i;
            int col = (old_orientation == 0) ? old_col + i : old_col;
            grid->cells[row][col].state = SHIP;
            grid->cells[row][col].ship_id = ship_id;
        }
        ship->start_row = old_row;
        ship->start_col = old_col;
        ship->orientation = old_orientation;
    }
}



bool is_ship_sunk(Grid *grid, int ship_id) {
  Ship *ship = &grid->ships[ship_id];
  if (ship->type == NO_SHIP) return false;

  for (int i = 0; i < ship->size; i++) {
    int row = (ship->orientation == 0) ? ship->start_row : ship->start_row + i;
    int col = (ship->orientation == 0) ? ship->start_col + i : ship->start_col;
    if (grid->cells[row][col].state != HIT) {
      return false; //at least one part of the ship is not hit
    }
  }
  return true; //all parts of the ship are hit
}






void cell_to_pixel(Grid *grid, int row, int col, int* x, int* y) {
  *x = grid->x + (col * CELL_WIDTH) + col;
  *y = grid->y + (row * CELL_HEIGHT) + row;
}



int coord_to_cell(const char* coord, int* row, int* col) {

  if (coord == NULL || strlen(coord) < 2) {
    return 1; // error: invalid coordinate
  }

  char col_letter = coord[0];
  if (col_letter < 'A' || col_letter > 'J') {
    return 1; // error: invalid column letter
  }
  *col = col_letter - 'A';

  int row_num;
  if (coord[2] == '\0') {
    row_num = coord[1] - '0';
  } else if (coord[1] == '1' && coord[2] == '0') {
    row_num = 10;
  } else {
    return 1; // error: invalid row number
  } 

  *row = row_num -1; // converting to index (0-9)

  if (*row < 0 || *row >= GRID_ROWS) return 1;
  return 0; 
}




bool can_place_ship(Grid *grid, int start_row, int start_col, int size, int orientation, int ship_id) {
  if (start_row < 0 || start_col < 0) return false;

  if (orientation == 0) { // horizontal
    if (start_col + size > GRID_COLS || start_row >= GRID_ROWS) return false;
  } else { // vertical
    if (start_row + size > GRID_ROWS || start_col >= GRID_COLS) return false;
  }

  for (int i = 0; i < size; i++) {
    int row = (orientation == 0) ? start_row : start_row + i;
    int col = (orientation == 0) ? start_col + i : start_col;
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        int check_row = row + dy;
        int check_col = col + dx;
        if (check_row < 0 || check_row >= GRID_ROWS ||
            check_col < 0 || check_col >= GRID_COLS)
          continue;
        if (grid->cells[check_row][check_col].state == SHIP && grid->cells[check_row][check_col].ship_id != ship_id)
          return false;
      }
    }
  }

  return true;
}



bool add_ship(Grid *grid, int ship_id, ShipType type, int orientation, const char* coord) {
  int row, col;
  int size = SHIP_TYPE_TO_SIZE(type);
  if (size == 0) return false;
  if (coord_to_cell(coord, &row, &col) != 0) return false;
  if (!can_place_ship(grid, row, col, size, orientation, ship_id)) return false;

  grid->ships[ship_id].type = type;
  grid->ships[ship_id].size = size;
  grid->ships[ship_id].orientation = orientation;
  grid->ships[ship_id].start_row = row;
  grid->ships[ship_id].start_col = col;

  for (int i = 0; i < size; i++) {
    int ship_row = (orientation == 0) ? row : row + i;
    int ship_col = (orientation == 0) ? col + i : col;
    grid->cells[ship_row][ship_col].state = SHIP;
    grid->cells[ship_row][ship_col].ship_id = ship_id;
  }
  return true;
}



void setup_ships(Grid *grid) {
  add_ship(grid, 0, SHIP_1, 0, "A1"); 
  add_ship(grid, 1, SHIP_1, 0, "E2");
  add_ship(grid, 2, SHIP_3, 0, "G3");
  add_ship(grid, 3, SHIP_2, 1, "D4"); 
  add_ship(grid, 4, SHIP_1, 0, "H6");
  add_ship(grid, 5, SHIP_4, 1, "B7");
  add_ship(grid, 6, SHIP_3, 1, "F7");
  add_ship(grid, 7, SHIP_2, 0, "H9"); 
}


void setup_pc_ships(Grid *grid) {
  ShipType ships_type[NUM_SHIPS] = {SHIP_1, SHIP_1, SHIP_3, SHIP_2, SHIP_1, SHIP_4, SHIP_3, SHIP_2};

  //from what i read we should move this to the main function !!!!!!!!!!!
  static int seeded = 0;
  if (!seeded) { srand(time(NULL)); seeded = 1; }

  //we randomly place ships on the grid
  for (int ship_id = 0; ship_id < NUM_SHIPS; ship_id++) {
    int placed = 0;
    int orientation, row, col, size = SHIP_TYPE_TO_SIZE(ships_type[ship_id]);
    while (!placed) {
      orientation = rand() % 2; 
      if (orientation == 0) {  //horizontal
        row = rand() % GRID_ROWS;
        col = rand() % (GRID_COLS - size + 1);
      } else { //vertical
        row = rand() % (GRID_ROWS - size + 1);
        col = rand() % GRID_COLS;
      }
      if (can_place_ship(grid, row, col, size, orientation, ship_id)) {
        grid->ships[ship_id].type = ships_type[ship_id];
        grid->ships[ship_id].size = size;
        grid->ships[ship_id].orientation = orientation;
        grid->ships[ship_id].start_row = row;
        grid->ships[ship_id].start_col = col;
        grid->ships[ship_id].status = ALIVE;
        for (int i = 0; i < size; i++) {
          int r = (orientation == 0) ? row : row + i;
          int c = (orientation == 0) ? col + i : col;
          grid->cells[r][c].state = SHIP;
          grid->cells[r][c].ship_id = ship_id;
        }
        placed = 1;
      }
    }
  }
}

