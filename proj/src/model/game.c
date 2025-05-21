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
}




void game_mouse_handler() {
  cursor_x += mouse_packet.delta_x * MOUSE_SPEED;
  cursor_y -= mouse_packet.delta_y * MOUSE_SPEED;

  if (cursor_x < 0) cursor_x = 0;
  if (cursor_x > mode_info.XResolution - cursor->width) cursor_x = mode_info.XResolution - cursor->width;
  if (cursor_y < 0) cursor_y = 0;
  if (cursor_y > mode_info.YResolution - cursor->height) cursor_y = mode_info.YResolution - cursor->height;  
}




void menu_main_loop() {
  draw_menu();
  draw_cursor(current_buffer);
  swap_buffers();
}

void info_main_loop() {
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
}

