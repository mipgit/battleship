#include "game_view.h"

extern Sprite *menu;
extern Sprite *arena;
extern Sprite *game_over;
extern Sprite *info;
extern Sprite *grid;

extern vbe_mode_info_t mode_info;




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
      fill_screen(BLACK);
      break;
  }
}


void draw_menu() {
  fill_screen(RED);
  draw_sprite(menu, mode_info.XResolution/2 - menu->width/2, mode_info.YResolution/2 - menu->height/2);
}

void draw_info() {
  fill_screen(BLUE);
  draw_sprite(info, mode_info.XResolution/2 - info->width/2, mode_info.YResolution/2 - info->height/2);
}

void draw_arena() {
  fill_screen(PINK);
  draw_sprite(grid, 0,0);
  //draw_sprite(arena, mode_info.XResolution/2 - arena->width/2, mode_info.YResolution/2 - arena->height/2);
}

void draw_game_over() {
  fill_screen(YELLOW);
  draw_sprite(game_over, mode_info.XResolution/2 - game_over->width/2, mode_info.YResolution/2 - game_over->height/2);
}

