#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <stdint.h>
#include "controller/graphics.h"

#include "xpm/arena.xpm"
#include "xpm/menu.xpm"
#include "xpm/game_over.xpm"
#include "xpm/info.xpm"



typedef struct {
  //int x, y; // current position
  int width, height; // dimensions
  //int xspeed, yspeed; // current speed
  uint32_t *map; // the pixmap (uint32_t !!!!!!!!!!!!)
} Sprite;


Sprite *menu;
Sprite *arena;
Sprite *game_over;
Sprite *info;



/**
* Creates a new sprite with pixmap "pic",
* with specified position (within the
* screen limits) and speed;
* Does not draw the sprite on the screen.
*
* @param pic lines of strings, same
* as xpm_map_t (has const protectors)
* @return NULL on invalid pixmap.
*/
Sprite *create_sprite(xpm_map_t sprite);

void destroy_sprite(Sprite *sp);



int move_sprite(Sprite *sp);

/* Some useful non-visible functions */
//static int draw_sprite(Sprite *sp, char *base); ->noutro sitio
//static int check_collision(Sprite *sp, char *base); ->might need this

//loaders and unloaders
int load_sprites();
void free_sprites();


#endif 
