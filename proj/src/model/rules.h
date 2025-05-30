#ifndef RULES_H
#define RULES_H

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
#include "view/rules_view.h"


extern uint8_t *rules_buffer;



void set_rules_buffer();
void init_rules();
void rules_main_loop();
void rules_keyboard_handler();







#endif
