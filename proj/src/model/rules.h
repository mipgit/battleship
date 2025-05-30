#ifndef RULES_H
#define RULES_H

#include <lcom/lcf.h>
#include "game.h"

extern uint8_t *rules_buffer;

void set_rules_buffer();
void init_rules();
void rules_main_loop();
void rules_keyboard_handler();

#endif