#include "game.h"



GameState state = MENU;


void set_state(GameState new_state) {
  state = new_state;
}

GameState get_state() {
  return state;
}



void game_keyboard_handler() {
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
      set_state(HELP);
      break;
    //case Q_KEY:
    //  set_state(GAME_OVER); //pode ser preciso para testar os desenhos
    //  break;    
    default:
      break;
  }
}




void game_mouse_handler() {
  cursor_x += mouse_packet.delta_x * MOUSE_SPEED;
  cursor_y -= mouse_packet.delta_y * MOUSE_SPEED;

  if (cursor_x < 0) cursor_x = 0;
  if (cursor_x > mode_info.XResolution - cursor->width) cursor_x = mode_info.XResolution - cursor->width;
  if (cursor_y < 0) cursor_y = 0;
  if (cursor_y > mode_info.YResolution - cursor->height) cursor_y = mode_info.YResolution - cursor->height;  
}





void help_main_loop() {
  draw_info();
  draw_cursor(current_buffer);
  swap_buffers();
}

void game_over_main_loop() {
  draw_game_over();
  draw_cursor(current_buffer);
  swap_buffers();
}



void free_buffers() {
  free_buffer(current_buffer);
  free_buffer(arena_buffer);
  free_buffer(menu_buffer);
}

