#ifndef GAME_OVER_VIEW_H
#define GAME_OVER_VIEW_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>

#include "controller/graphics.h"

#include "model/game_macro.h"
#include "model/game.h"
#include "model/sprite.h"
#include "model/game_over.h"
#include "view/sprite_view.h"


#define OPTION_MENU_Y 340  // Y position for "Menu" option
#define OPTION_EXIT_Y 400  // Y position for "Exit" option
#define OPTIONS_X 300      // X position for both options

#define WINNER_TEXT_Y 200 // Y position for the winner text


void draw_game_over_background(uint8_t *buffer);

void draw_game_over_screen();

void draw_game_over_winner(uint8_t *buffer);

void draw_game_over_options(uint8_t *buffer);

#endif
