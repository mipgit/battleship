#include "arena_view.h"

extern uint8_t *current_buffer;
extern Sprite *grid;
extern Sprite *ship1;
extern Sprite *ship2h;
extern Sprite *ship2v;
extern Sprite *ship3h;
extern Sprite *ship3v;
extern Sprite *ship4v;


void draw_arena() {
  fill_screen(PINK, current_buffer);
  draw_sprite(grid, 0,0, current_buffer);
  draw_sprite(ship1, 31, 31, current_buffer);
  draw_sprite(ship1, 31 + 33*4 + 4, 31 + 33*1 + 1, current_buffer);
  draw_sprite(ship1, 31 + 33*7 + 7, 31 + 33*5 + 5, current_buffer);
  draw_sprite(ship2h, 269, 303, current_buffer); //31 + 33*7 + 7 , 31 + 33*8 + 8
  draw_sprite(ship2v, 133, 133, current_buffer);  //31(início) + 33*3(quadrados) + 3(linhas)
  draw_sprite(ship3h, 235, 99, current_buffer); //31 + 33*6 + 6 , 31 + 33*2 + 2
  draw_sprite(ship3v, 201, 235, current_buffer); //31 + 33*5 + 5 , 31 + 33*6 + 6
  draw_sprite(ship4v, 65, 235, current_buffer); //31 + 33*1 + 1, 31 + 33*6 + 6
}


