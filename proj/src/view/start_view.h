#ifndef START_VIEW_H
#define START_VIEW_H


#include <minix/sysutil.h>
#include <lcom/lcf.h>

#include "controller/graphics.h"

#include "model/game_macro.h"
#include "model/game.h"
#include "model/sprite.h"
#include "model/start.h"
#include "view/sprite_view.h"


#define OPTIONS_X         300   // X position for all options

#define OPTION_START_Y    270   // Y position for "Start"
#define OPTION_RULES_Y    340   // Y position for "Rules"
#define OPTION_HELP_Y     410   // Y position for "Help"


void draw_start_background(uint8_t *buffer);
void draw_start();
void draw_start_options(uint8_t *buffer);






#endif 
