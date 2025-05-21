#ifndef ARENA_H
#define ARENA_H


#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "controller/graphics.h"
#include "model/game_macro.h"
#include "model/game.h"
#include "view/game_view.h"
#include "view/arena_view.h"


extern uint8_t *arena_buffer;

Arena arena;



void arena_main_loop();

void arena_keyboard_handler();

void arena_mouse_handler();
void handle_mouse_click(Grid *grid, int mouse_x, int mouse_y);

void set_arena_buffer();
void reset_arena_state(); //de cada vez que o jogo acabar, se o utilizador quiser outro jogo chamamos esta func


void init_grid(Grid *grid);
void cell_to_pixel(Grid *grid, int row, int col, int* x, int* y);
int coord_to_cell(const char* coord, int* row, int* col);
bool can_place_ship(Grid *grid, int start_row, int start_col, int size, int orientation);
bool add_ship(Grid *grid, int ship_id, ShipType type, int orientation, const char* coord);
void setup_ships(Grid *grid);



#endif
