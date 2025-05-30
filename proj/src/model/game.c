#include "game.h"


GameState state = MENU;
GameState previous_state = MENU;


void set_state(GameState new_state) {
  if (new_state == state) return;
  previous_state = state;
  state = new_state;
}

GameState get_state() {
  return state;
}

GameState get_previous_state() {
  return previous_state;
}

//feito para testar os ecrãs
void game_keyboard_handler() {
  switch (scancode) {
    case M_KEY:
      set_state(MENU);
      scancode = 0; 
      break;
    case SPACE_KEY:
       if (state != RULES && state != HELP) set_state(RULES); 
       scancode = 0;
       break;
    case H_KEY:
       if (state != HELP && state != RULES) set_state(HELP);
       scancode = 0;
       break;   
    case ESC_KEY:
       set_state(EXIT);
       break;    
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









void free_buffers() {
  free_buffer(current_buffer);
  free_buffer(arena_buffer);
  free_buffer(menu_buffer);
  free_buffer(start_buffer);
  free_buffer(mode_buffer);
  free_buffer(rules_buffer);
  free_buffer(help_buffer);
  free_buffer(game_over_buffer);
}

