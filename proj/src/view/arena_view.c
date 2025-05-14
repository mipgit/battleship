#include "arena_view.h"

extern uint8_t *current_buffer;
extern Sprite *grid;


void draw_arena() {
  fill_screen(PINK, current_buffer);
  draw_sprite(grid, 0,0, current_buffer);
}


