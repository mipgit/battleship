#include "arena.h"


void arena_main_loop() { 
  draw_arena();
  draw_cursor(current_buffer);
  swap_buffers();

  //lidar com os handler aqui? idk
}


void reset_arena_state() {
  init_grid(&arena.player1_grid);
  setup_ships(&arena.player1_grid);
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



void cell_to_pixel(int row, int col, int* x, int* y) {
  *x = GRID_ORIGIN_X + (col * CELL_WIDTH) + col;
  *y = GRID_ORIGIN_Y + (row * CELL_HEIGHT) + row;
}


int pixel_to_cell(int x, int y, int* row, int* col) {
    x -= GRID_ORIGIN_X;
    y -= GRID_ORIGIN_Y;

    *col = x / (CELL_WIDTH + 1);
    *row = y / (CELL_HEIGHT + 1);

    if (*row < 0 || *row >= GRID_ROWS || *col < 0 || *col >= GRID_COLS) {
        return 1; // error: outside grid
    }

    return 0;
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
  add_ship(grid, 1, SHIP_2, 0, "D5"); 
  add_ship(grid, 2, SHIP_1, 0, "J8"); 
}


