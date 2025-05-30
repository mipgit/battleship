#include "start.h"

extern uint8_t *current_buffer;
uint8_t *start_buffer;
extern unsigned int frame_size;


extern uint8_t scancode;

static StartOption selected_option = GO_START;


void set_start_buffer() {
  if (start_buffer == NULL) {
    start_buffer = (uint8_t *) malloc(frame_size);
  }
}

void init_start() {
  set_start_buffer();
  draw_start_background(start_buffer);
}


void start_main_loop() {
  draw_start();
  draw_cursor(current_buffer); 
  swap_buffers();
}


void start_keyboard_handler() {
  if (scancode == UP_ARROW_KEY) {
      if (selected_option == GO_START)
          selected_option = GO_HELP;
      else
          selected_option = (StartOption)(selected_option - 1);
  }
  else if (scancode == DOWN_ARROW_KEY) {
      if (selected_option == GO_HELP)
          selected_option = GO_START;
      else
          selected_option = (StartOption)(selected_option + 1);
  } 
  else if (scancode == ENTER_KEY) {
      if (selected_option == GO_START) {
          set_state(MODE);
      }
      else if (selected_option == GO_RULES) {
          set_state(RULES);
      }
      else if (selected_option == GO_HELP) {
          set_state(HELP);
      }
  }
}


StartOption get_start_option() {
  return selected_option;
}

void set_start_option(StartOption option) {
  selected_option = option;
}
