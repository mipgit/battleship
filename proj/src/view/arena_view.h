#ifndef ARENA_VIEW_H
#define ARENA_VIEW_H



#include <minix/sysutil.h>
#include <lcom/lcf.h>

#include "controller/graphics.h"

#include "model/game_macro.h"
#include "model/game.h"
#include "model/sprite.h"
#include "model/arena.h"
#include "view/sprite_view.h"


void draw_arena_background(uint8_t *buffer);
void draw_arena();
void draw_grid(Grid *grid);

void draw_cell(Grid *grid, int x, int y, int cell_row, int cell_col);
void draw_ship_sprite(int x, int y,  ShipType type, int orientation);
void draw_hit_marker(int x, int y);
void draw_miss_marker(int x, int y);

#endif
