#include "arena.h"


void arena_main_loop() {
  draw_arena();
  draw_cursor(current_buffer);
  swap_buffers();
}



