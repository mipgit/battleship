#ifndef SPRITE_VIEW_H
#define SPRITE_VIEW_H


#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <minix/sysutil.h>

#include "controller/graphics.h"
#include "model/sprite.h"
#include "model/game_macro.h"




int(draw_sprite)(Sprite *sprite, uint16_t x, uint16_t y, uint8_t *buffer);

//to write stuff
int(draw_char)(char c, uint16_t x, uint16_t y, uint32_t color);
int(draw_string)(char str[], uint16_t x, uint16_t y, uint32_t color);

int(draw_sprite_highlighted)(Sprite *sprite, uint16_t x, uint16_t y, uint8_t *buffer);





#endif
