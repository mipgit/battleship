#include "menu.h"

extern uint8_t *current_buffer;
uint8_t *menu_buffer;
extern unsigned int frame_size;



void set_menu_buffer() {
  if (menu_buffer == NULL) {
    menu_buffer = (uint8_t *) malloc(frame_size);
  }
}

void init_menu() {
  set_menu_buffer();
  draw_menu_background(menu_buffer);
}


void menu_main_loop() {
  draw_menu();
  draw_cursor(current_buffer); //mas nos ecrãs posso desenhar para o current, não é preciso fazer dco  dois
  swap_buffers();
}


