#ifndef MODE_H
#define MODE_H


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

#include "view/mode_view.h"

extern GameMode mode;

void set_mode_buffer();
void init_mode();
void mode_main_loop();
void mode_keyboard_handler();












#endif
