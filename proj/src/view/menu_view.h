#ifndef MENU_VIEW_H
#define MENU_VIEW_H


#include <minix/sysutil.h>
#include <lcom/lcf.h>

#include "controller/graphics.h"
#include "controller/rtc.h"

#include "model/game_macro.h"
#include "model/game.h"
#include "model/sprite.h"
#include "model/menu.h"
#include "view/sprite_view.h"

bool daytime(uint8_t hour, uint8_t minute);
void draw_menu_background(uint8_t *buffer);
void draw_menu();


#endif 
