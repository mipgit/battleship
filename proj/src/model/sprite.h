#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <stdint.h>
#include "controller/graphics.h"
#include "xpm/info.xpm"
#include "xpm/batalha_naval_layout.xpm"
#include "xpm/one_grid_layout.xpm"
#include "xpm/cursor.xpm"
#include "xpm/ship1.xpm"
#include "xpm/ship2h.xpm"
#include "xpm/ship2v.xpm"
#include "xpm/ship3h.xpm"
#include "xpm/ship3v.xpm"
#include "xpm/ship4h.xpm"
#include "xpm/ship4v.xpm"
#include "xpm/player1.xpm"
#include "xpm/player2.xpm"
#include "xpm/menu_shipR.xpm"
#include "xpm/menu_shipL.xpm"
#include "xpm/logo.xpm"
#include "xpm/game_over.xpm"
#include "xpm/menU.xpm"
#include "xpm/exit.xpm"
#include "xpm/mode.xpm"
#include "xpm/single_player.xpm"
#include "xpm/multi_player.xpm"



typedef struct {
  //int x, y; // current position
  int width, height; // dimensions
  //int xspeed, yspeed; // current speed
  uint32_t *map; // the pixmap (uint32_t !!!!!!!!!!!!)
} Sprite;


Sprite *info;
Sprite *double_grid;
Sprite *single_grid;
Sprite *cursor;
Sprite *ship1;
Sprite *ship2h;
Sprite *ship2v;
Sprite *ship3h;
Sprite *ship3v;
Sprite *ship4h;
Sprite *ship4v;
Sprite *player1;
Sprite *player2;
Sprite *menu_shipR;
Sprite *menu_shipL;
Sprite *logo;
Sprite *game_over;
Sprite *menu_option;
Sprite *exit_option;
Sprite *choose_mode;
Sprite *single_player;
Sprite *multi_player;


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
