#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>

#include "controller/timer.h"
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/graphics.h"

#include "model/game.h"
#include "model/sprite.h"
#include "view/sprite_view.h"



void draw_screen();

void draw_menu();
void draw_info();
void draw_arena(); //isto vai ter de passar para outro ficheiro penso eu (vai ser muita coisa)
void draw_game_over();




#endif
