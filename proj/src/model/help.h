#ifndef HELP_H
#define HELP_H

#include <lcom/lcf.h>
#include "game.h"

extern uint8_t *help_buffer;

void set_help_buffer();
void init_help();
void help_main_loop();
void help_keyboard_handler();

#endif