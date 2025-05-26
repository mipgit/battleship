#include "menu_view.h"

extern uint8_t *current_buffer;
extern uint8_t *menu_buffer;
extern unsigned int frame_size;
extern vbe_mode_info_t mode_info;

extern Sprite *menu_shipR;
extern Sprite *menu_shipL;
extern Sprite *logo;




void draw_menu_background(uint8_t *buffer) {
  fill_screen(TEAL, buffer);
  draw_sprite(logo, 5, 55, buffer);
}


void draw_menu() {
  memcpy(current_buffer, menu_buffer, frame_size);

  static int x = 0;
  static int dx = 2;
  int y = 400 - menu_shipR->height / 2;

  x += dx;
  if (x < 0) {
    x = 0;
    dx = -dx;
  }
  if (x > (int)(mode_info.XResolution - menu_shipR->width)) {
    x = mode_info.XResolution - menu_shipR->width;
    dx = -dx;
  }

  Sprite *sprite_to_draw = (dx > 0) ? menu_shipR : menu_shipL;
  draw_sprite(sprite_to_draw, x, y, current_buffer);
}


