#ifndef GAME_OVER_H
#define GAME_OVER_H

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


typedef enum {
  GO_MENU = 0,
  GO_EXIT = 1
} GameOverOption;


extern uint8_t *game_over_buffer;


void set_game_over_buffer();
void init_game_over();
void game_over_main_loop();


void game_over_keyboard_handler();
void game_over_mouse_handler();


bool is_mouse_over_option(GameOverOption option);

GameOverOption get_game_over_option();

void set_game_over_option(GameOverOption option);





#endif

