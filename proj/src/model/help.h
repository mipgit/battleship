#ifndef HELP_H
#define HELP_H

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
#include "view/help_view.h"


extern uint8_t *help_buffer;


void set_help_buffer();
void init_help();
void help_main_loop();
void help_keyboard_handler();







#endif
