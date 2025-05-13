#include "game.h"

#define ESC_KEY 0x81
#define Q_KEY 0x10
#define SPACE_KEY 0x39
#define M_KEY 0x32
#define ENTER_KEY 0x1C


GameState state = MENU;


void set_state(GameState new_state) {
  state = new_state;
}

GameState get_state() {
  return state;
}



void game_keyboard_handler() {
  kbc_ih();
  switch (scancode) {
    case ESC_KEY:
      set_state(EXIT);
      break;
    case M_KEY:
      set_state(MENU);
      break;
    case ENTER_KEY:
      set_state(ARENA);
      break;
    case SPACE_KEY:
      set_state(INFO);
      break;
    case Q_KEY:
      set_state(GAME_OVER);
      break;    
    default:
      break;
  }
  draw_screen();
}
