// INCOMPLETO

#ifndef HELP_VIEW_H
#define HELP_VIEW_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/graphics.h"
#include "model/game.h"

/**
 * @brief Draws the static help/controls screen (XPM)
 * @param buffer Target video buffer
 */
void draw_help(uint8_t *buffer);

#endif