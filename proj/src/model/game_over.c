#include "game_over.h"
#include "view/game_over_view.h"

extern uint8_t *current_buffer;
uint8_t *game_over_buffer = NULL;
extern unsigned int frame_size;
extern GameState state;
extern int cursor_x;
extern int cursor_y;
extern struct packet mouse_packet;

extern Sprite *menu_option;
extern Sprite *exit_option;

static GameOverOption selected_option = GO_MENU;

void set_game_over_buffer() {
  if (game_over_buffer == NULL) {
    game_over_buffer = (uint8_t *) malloc(frame_size);
  }
}

void init_game_over() {
  set_game_over_buffer();
  if (game_over_buffer != NULL) {
    draw_game_over_background(game_over_buffer);
  }
  selected_option = GO_MENU;
}

void game_over_main_loop() {
  draw_game_over_screen();
  draw_cursor(current_buffer);
  swap_buffers();
}

void game_over_keyboard_handler() {
  extern uint8_t scancode;
  
  if (scancode == UP_ARROW_KEY) {
      selected_option = GO_MENU;
  }
  else if (scancode == DOWN_ARROW_KEY) {
      selected_option = GO_EXIT;
  }
  else if (scancode == ENTER_KEY) {
      if (selected_option == GO_MENU) {
          set_state(START);
      }
      else if (selected_option == GO_EXIT) {
          set_state(EXIT);
      }
  }
}


bool is_mouse_over_option(GameOverOption option) {
  if (option == GO_MENU) {
      return (cursor_x >= OPTIONS_X && 
              cursor_x <= OPTIONS_X + menu_option->width &&
              cursor_y >= OPTION_MENU_Y && 
              cursor_y <= OPTION_MENU_Y + menu_option->height);
  }
  else if (option == GO_EXIT) {
      return (cursor_x >= OPTIONS_X && 
              cursor_x <= OPTIONS_X + exit_option->width &&
              cursor_y >= OPTION_EXIT_Y && 
              cursor_y <= OPTION_EXIT_Y + exit_option->height);
  }
  return false;
}

void game_over_mouse_handler() {
  if (is_mouse_over_option(GO_MENU)) {
      selected_option = GO_MENU;
      
      if (mouse_packet.lb) {
          set_state(MENU);
      }
  }
  else if (is_mouse_over_option(GO_EXIT)) {
      selected_option = GO_EXIT;
      
      if (mouse_packet.lb) {
          set_state(EXIT);
      }
  }
}


GameOverOption get_game_over_option() {
  return selected_option;
}

void set_game_over_option(GameOverOption option) {
  selected_option = option;
}
