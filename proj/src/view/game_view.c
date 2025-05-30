#include "game_view.h"

extern Sprite *game_over;
extern Sprite *info;
extern Sprite *cursor;
extern Sprite *menu_shipR;
extern Sprite *menu_shipL;
extern Sprite *logo;
extern Sprite *bomb;

extern vbe_mode_info_t mode_info;
extern uint8_t *current_buffer;

extern int cursor_x;
extern int cursor_y;

extern PlayerTurn current_player;
extern ArenaPhase arena_phase;


void draw_cursor(uint8_t *buffer) {
  if (get_state() == ARENA && arena_phase == BATTLE_PHASE) draw_sprite(bomb, cursor_x, cursor_y, buffer);
  else draw_sprite(cursor, cursor_x, cursor_y, buffer);
}



void draw_info() {
  fill_screen(PINK, current_buffer);
  draw_sprite(info, mode_info.XResolution/2 - info->width/2, mode_info.YResolution/2 - info->height/2, current_buffer);
}




