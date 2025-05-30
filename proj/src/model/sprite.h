#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <stdint.h>
#include "controller/graphics.h"

#include "xpm/cursor.xpm"
#include "xpm/bomb.xpm"

#include "xpm/ships/ship1.xpm"
#include "xpm/ships/ship2h.xpm"
#include "xpm/ships/ship2v.xpm"
#include "xpm/ships/ship3h.xpm"
#include "xpm/ships/ship3v.xpm"
#include "xpm/ships/ship4h.xpm"
#include "xpm/ships/ship4v.xpm"

#include "xpm/arena/player1.xpm"
#include "xpm/arena/player2.xpm"
#include "xpm/arena/setup.xpm"
#include "xpm/arena/one_grid_layout.xpm"

#include "xpm/options/start_option.xpm"
#include "xpm/options/rules_option.xpm"
#include "xpm/options/help_option.xpm"
#include "xpm/options/menu_option.xpm"
#include "xpm/options/exit_option.xpm"

#include "xpm/mode/mode.xpm"
#include "xpm/mode/single_player.xpm"
#include "xpm/mode/multi_player.xpm"

#include "xpm/menu/menu_shipR.xpm"
#include "xpm/menu/menu_shipL.xpm"
#include "xpm/menu/sun.xpm"
#include "xpm/menu/moon.xpm"
#include "xpm/menu/cloud.xpm"
#include "xpm/menu/star.xpm"
#include "xpm/menu/press_enter.xpm"

#include "xpm/game_over/game_over.xpm"
#include "xpm/game_over/wins.xpm"

#include "xpm/rules/rules_text.xpm"
#include "xpm/rules/rules.xpm"

#include "xpm/help/back.xpm"
#include "xpm/help/help.xpm"
#include "xpm/help/options.xpm"

#include "xpm/logo.xpm"



typedef struct {
  //int x, y; // current position
  int width, height; // dimensions
  //int xspeed, yspeed; // current speed
  uint32_t *map; // the pixmap (uint32_t !!!!!!!!!!!!)
} Sprite;


Sprite *cursor;
Sprite *bomb; 

Sprite *ship1;
Sprite *ship2h;
Sprite *ship2v;
Sprite *ship3h;
Sprite *ship3v;
Sprite *ship4h;
Sprite *ship4v;

Sprite *player1;
Sprite *player2;
Sprite *setup;
Sprite *single_grid;

Sprite *menu_shipR;
Sprite *menu_shipL;
Sprite *sun;
Sprite *moon;
Sprite *cloud;
Sprite *star;
Sprite *press_enter;
Sprite *rules_text;
Sprite *rules;


Sprite *start_option;
Sprite *rules_option;
Sprite *help_option;
Sprite *menu_option;
Sprite *exit_option;

Sprite *choose_mode;
Sprite *single_player;
Sprite *multi_player;

Sprite *logo;
Sprite *rules_content;
Sprite *help_content;
Sprite *game_over;
Sprite *wins;

Sprite *help;
Sprite *help_options;
Sprite *go_back;


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

