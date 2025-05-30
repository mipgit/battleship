/**
 * @file sprite.h
 * @brief Sprite management for the Battleship game
 * 
 * This file contains declarations for sprite-related functionality, including
 * sprite creation, destruction, and manipulation. It also declares all the game
 * sprites used across different game screens.
 */

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

#include "xpm/logo.xpm"
#include "xpm/rules.xpm"
#include "xpm/help.xpm"
#include "xpm/game_over.xpm"
#include "xpm/wins.xpm"


/**
 * @struct Sprite
 * @brief Represents a sprite with its dimensions and pixel map
 */
typedef struct {
  int width;   ///< Width of the sprite in pixels
  int height;  ///< Height of the sprite in pixels
  uint32_t *map; ///< Pointer to the sprite's pixel data
} Sprite;


/// @brief Cursor sprite controlled by the mouse
extern Sprite *cursor;

/// @brief Bomb sprite used for attacks
extern Sprite *bomb;

/// @brief One-cell ship sprite
extern Sprite *ship1;

/// @brief Two-cell horizontal ship sprite
extern Sprite *ship2h;

/// @brief Two-cell vertical ship sprite
extern Sprite *ship2v;

/// @brief Three-cell horizontal ship sprite
extern Sprite *ship3h;

/// @brief Three-cell vertical ship sprite
extern Sprite *ship3v;

/// @brief Four-cell horizontal ship sprite
extern Sprite *ship4h;

/// @brief Four-cell vertical ship sprite
extern Sprite *ship4v;

/// @brief Player 1 label sprite
extern Sprite *player1;

/// @brief Player 2 label sprite
extern Sprite *player2;

/// @brief Setup screen sprite
extern Sprite *setup;

/// @brief Single grid layout sprite
extern Sprite *single_grid;

/// @brief Right-facing menu ship decoration sprite
extern Sprite *menu_shipR;

/// @brief Left-facing menu ship decoration sprite
extern Sprite *menu_shipL;

/// @brief Sun decoration sprite
extern Sprite *sun;

/// @brief Moon decoration sprite
extern Sprite *moon;

/// @brief Cloud decoration sprite
extern Sprite *cloud;

/// @brief Star decoration sprite
extern Sprite *star;

/// @brief "Press Enter" prompt sprite
extern Sprite *press_enter;

/// @brief "Start" menu option sprite
extern Sprite *start_option;

/// @brief "Rules" menu option sprite
extern Sprite *rules_option;

/// @brief "Help" menu option sprite
extern Sprite *help_option;

/// @brief "Menu" option sprite
extern Sprite *menu_option;

/// @brief "Exit" option sprite
extern Sprite *exit_option;

/// @brief Mode selection screen title sprite
extern Sprite *choose_mode;

/// @brief Single player mode option sprite
extern Sprite *single_player;

/// @brief Multiplayer mode option sprite
extern Sprite *multi_player;

/// @brief Game logo sprite
extern Sprite *logo;

/// @brief Rules screen content sprite
extern Sprite *rules_content;

/// @brief Help screen content sprite
extern Sprite *help_content;

/// @brief Game over screen title sprite
extern Sprite *game_over;

/// @brief Winner announcement sprite
extern Sprite *wins;


/**
 * @brief Creates a new sprite from an XPM
 * 
 * Allocates memory for a sprite structure and loads the provided XPM image
 * into its pixel map.
 *
 * @param sprite XPM data to convert into a sprite
 * @return Pointer to the new sprite on success, NULL on failure
 */
Sprite *create_sprite(xpm_map_t sprite);

void destroy_sprite(Sprite *sp);



/**
 * @brief Destroys a sprite and frees associated memory
 * 
 * @param sp Pointer to the sprite to destroy
 */
void destroy_sprite(Sprite *sp);

/**
 * @brief Moves a sprite according to its speed
 * 
 * @param sp Pointer to the sprite to move
 * @return 0 on success, non-zero otherwise
 */
int move_sprite(Sprite *sp);

/**
 * @brief Loads all game sprites from their XPM files
 * 
 * Creates all sprites used in the game by loading their XPM data.
 * 
 * @return 0 on success, non-zero on failure
 */
int load_sprites();

/**
 * @brief Frees all game sprites and their associated memory
 */
void free_sprites();


#endif 

