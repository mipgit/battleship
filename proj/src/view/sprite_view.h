#ifndef SPRITE_VIEW_H
#define SPRITE_VIEW_H


#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <minix/sysutil.h>

#include "controller/graphics.h"
#include "model/sprite.h"


#define BLACK 0x000000
#define RED 0xFF0000
#define PINK 0xFF00FF
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define HOVER_COLOR 0xAAAAFF


int(draw_sprite)(Sprite *sprite, uint16_t x, uint16_t y, uint8_t *buffer);

//to write stuff
int(draw_char)(char c, uint16_t x, uint16_t y, uint32_t color);
int(draw_string)(char str[], uint16_t x, uint16_t y, uint32_t color);







#endif
