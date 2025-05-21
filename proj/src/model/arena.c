#include "arena.h"

extern vbe_mode_info_t mode_info;
extern struct packet mouse_packet; 
extern int cursor_x, cursor_y;
extern uint8_t *current_buffer;
uint8_t *arena_buffer;
extern unsigned int frame_size;


void arena_main_loop() { 
  draw_arena();
  draw_cursor(current_buffer);
  swap_buffers();
}


void arena_mouse_handler() {
  static bool prev_lb = false;
  bool curr_lb = mouse_packet.lb;

  //i just want to handle once per click. if the button is held down continuously this 
  //will lead to unecesasaring processement of code 
  if (curr_lb && !prev_lb) {
    handle_mouse_click(&arena.player1_grid, cursor_x, cursor_y); 
    handle_mouse_click(&arena.player2_grid, cursor_x, cursor_y); 
  }

  prev_lb = curr_lb;
}



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
        } else if (cell->state == EMPTY) {
          cell->state = MISS;
        }
        return;
      }
    }
  }
}



void set_arena_buffer() {
  if (arena_buffer == NULL) {
    arena_buffer = (uint8_t *) malloc(frame_size);
  }
}



void reset_arena_state() {
  //set grid origins (fix this!!!)
  arena.player1_grid.sprite_x = 10;
  arena.player1_grid.sprite_y = 10;
  arena.player1_grid.x = arena.player1_grid.sprite_x + 31;
  arena.player1_grid.y = arena.player1_grid.sprite_y + 31;
  

  arena.player2_grid.sprite_x = 410;
  arena.player2_grid.sprite_y = 10;
  arena.player2_grid.x = arena.player2_grid.sprite_x + 31;
  arena.player2_grid.y = arena.player2_grid.sprite_y + 31;

  //draw background
  set_arena_buffer();
  draw_arena_background(arena_buffer);



  //initialize grids and ships

  //player 1
  init_grid(&arena.player1_grid);
  setup_ships(&arena.player1_grid);

  //player 2
  init_grid(&arena.player2_grid);
  setup_ships(&arena.player2_grid);
}


void init_grid(Grid *grid) {
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
  }
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




bool can_place_ship(Grid *grid, int start_row, int start_col, int size, int orientation) {
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
        if (grid->cells[check_row][check_col].state == SHIP)
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
  if (!can_place_ship(grid, row, col, size, orientation)) return false;

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
  add_ship(grid, 0, SHIP_3, 0, "A1"); 
  add_ship(grid, 1, SHIP_2, 1, "D5"); 
  add_ship(grid, 2, SHIP_1, 0, "J8"); 
}


