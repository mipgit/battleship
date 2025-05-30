#include "game_view.h"

extern Sprite *game_over;
extern Sprite *info;
extern Sprite *cursor;
extern Sprite *menu_shipR;
extern Sprite *menu_shipL;
extern Sprite *logo;

extern vbe_mode_info_t mode_info;
extern uint8_t *current_buffer;

extern int cursor_x;
extern int cursor_y;

extern PlayerTurn current_player;
extern Sprite *player1s;
extern Sprite *player2s;

void draw_cursor(uint8_t *buffer) {
  draw_sprite(cursor, cursor_x, cursor_y, buffer);
}


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




void draw_info() {
  fill_screen(PINK, current_buffer);
  draw_sprite(info, mode_info.XResolution/2 - info->width/2, mode_info.YResolution/2 - info->height/2, current_buffer);
}

void draw_game_over() {
  fill_screen(BLUE, current_buffer);

  if (current_player == PLAYER_1) {
    draw_sprite(player1s, mode_info.XResolution/2 - player1s->width/2, mode_info.YResolution/2 - player1s->height/2, current_buffer);
  } else if (current_player == PLAYER_2) {
    draw_sprite(player2s, mode_info.XResolution/2 - player2s->width/2, mode_info.YResolution/2 - player2s->height/2, current_buffer);
  }  
}




