/**
 * @file game_view.h
 * @brief This file contains general view-related functions for the game,
 * such as drawing the mouse cursor.
 */

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/timer.h"
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/graphics.h"
#include "model/game.h"
#include "model/sprite.h"
#include "view/sprite_view.h"

/**
 * @brief Draws the mouse cursor on the screen.
 * @param buffer Pointer to the graphics buffer where the cursor will be drawn.
 */
void draw_cursor(uint8_t *buffer);

#endif
