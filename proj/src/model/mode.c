#include "mode.h"


extern uint8_t *current_buffer;
extern unsigned int frame_size;

extern uint8_t scancode;

GameMode mode;




void mode_main_loop() {
  draw_mode();
  draw_cursor(current_buffer);
  swap_buffers();
}



void mode_keyboard_handler() {
  switch (scancode) {
    case ONE_KEY:
      set_state(ARENA);
      mode = SINGLE_PLAYER;
      break;
    case TWO_KEY:
      set_state(ARENA);  
      mode = MULTI_PLAYER;
      break;
    default:
      break;
  }
}









