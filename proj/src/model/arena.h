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

extern ArenaPhase arena_phase;
extern Arena arena;


extern PlayerTurn current_player;


// Drag structure to handle ship dragging
typedef struct {
    bool dragging;
    int ship_id;                //id of the ship being dragged
    int origin_row, origin_col; //where the drag started
    int orientation;            //orientation of the ship being dragged
    Grid *active_grid;          //grid where the ship is being dragged
} DragState;

extern DragState drag_state;




void arena_main_loop();

void set_arena_buffer();
void init_arena(); //de cada vez que o jogo acabar, se o utilizador quiser outro jogo chamamos esta func

void init_grid(Grid *grid, int sprite_x, int sprite_y);


void arena_keyboard_handler();


void arena_mouse_handler();

void handle_mouse_click(Grid *grid, int mouse_x, int mouse_y);


void battle_phase(bool curr_lb, bool prev_lb);
void setup_phase(bool curr_lb, bool prev_lb, Grid *grid);


bool mouse_over_ship(Grid *grid, int mouse_x, int mouse_y, int *row, int *col, int *ship_id);
bool mouse_over_cell(Grid *grid, int mouse_x, int mouse_y, int *row, int *col);
void move_ship(Grid *grid, int ship_id, int new_row, int new_col, int orientation);

bool is_ship_sunk(Grid *grid, int ship_id);


void cell_to_pixel(Grid *grid, int row, int col, int* x, int* y);
int coord_to_cell(const char* coord, int* row, int* col);
bool can_place_ship(Grid *grid, int start_row, int start_col, int size, int orientation, int ship_id);
bool add_ship(Grid *grid, int ship_id, ShipType type, int orientation, const char* coord);
void setup_ships(Grid *grid);
void setup_pc_ships(Grid *grid);


#endif
