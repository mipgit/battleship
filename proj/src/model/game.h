#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "controller/timer.h"
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/graphics.h"

#include "view/game_view.h"


typedef enum {
  MENU,
  INFO,
  ARENA,
  GAME_OVER,
  EXIT
} GameState;


extern uint8_t scancode;
extern uint8_t byte_index;

extern GameState state;


void set_state(GameState new_state);
GameState get_state();

void game_timer_handler();
void game_keyboard_handler();
void game_mouse_handler();



#endif
