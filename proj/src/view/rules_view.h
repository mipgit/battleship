// INCOMPLETO

#ifndef RULES_VIEW_H
#define RULES_VIEW_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/graphics.h"
#include "model/game.h"

/**
 * @brief Draws the static rules screen (XPM)
 * @param buffer Target video buffer
 */
void draw_rules(uint8_t *buffer);

#endif