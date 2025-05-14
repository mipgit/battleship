#include "game_view.h"

extern Sprite *menu;
extern Sprite *arena;
extern Sprite *game_over;
extern Sprite *info;
extern Sprite *cursor;

extern vbe_mode_info_t mode_info;
extern uint8_t *current_buffer;

extern int cursor_x;
extern int cursor_y;



void draw_cursor(uint8_t *buffer) {
  draw_sprite(cursor, cursor_x, cursor_y, buffer);
}



/*
void draw_screen() {
  switch (get_state()) {
    case MENU:
      draw_menu();
      break;
    case INFO:
      draw_info();
      break;
    case ARENA:
      draw_arena();
      break;
    case GAME_OVER:
      draw_game_over();
      break;
    case EXIT:
      fill_screen(BLACK, current_buffer);
      break;
  }
  draw_cursor(current_buffer);
}
*/


void draw_menu() {
  fill_screen(RED, current_buffer);
  draw_sprite(menu, mode_info.XResolution/2 - menu->width/2, mode_info.YResolution/2 - menu->height/2, current_buffer);
}

void draw_info() {
  fill_screen(BLUE, current_buffer);
  draw_sprite(info, mode_info.XResolution/2 - info->width/2, mode_info.YResolution/2 - info->height/2, current_buffer);
}

void draw_game_over() {
  fill_screen(YELLOW, current_buffer);
  draw_sprite(game_over, mode_info.XResolution/2 - game_over->width/2, mode_info.YResolution/2 - game_over->height/2, current_buffer);
}




