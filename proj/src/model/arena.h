#ifndef ARENA_H
#define ARENA_H


#include <lcom/lcf.h>
#include "controller/graphics.h"

#include "model/game.h"
#include "view/game_view.h"
#include "view/arena_view.h"


extern uint8_t *current_buffer;

void arena_main_loop();

void arena_keyboard_handler();
void arena_mouse_handler();




#endif
