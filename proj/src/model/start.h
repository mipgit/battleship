#ifndef START_H
#define START_H

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
#include "view/start_view.h"


extern uint8_t *start_buffer;


typedef enum {
    GO_START, 
    GO_RULES,
    GO_HELP,
} StartOption;



void set_start_buffer();
void init_start();
void start_main_loop();
void start_keyboard_handler();

StartOption get_start_option();
void set_start_option(StartOption option);





#endif
