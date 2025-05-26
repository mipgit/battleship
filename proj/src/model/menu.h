#ifndef MENU_H
#define MENU_H

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
#include "view/menu_view.h"


extern uint8_t *menu_buffer;


void set_menu_buffer();
void init_menu();
void menu_main_loop();








#endif
