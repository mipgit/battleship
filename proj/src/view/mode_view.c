#include "mode_view.h"

extern uint8_t *current_buffer;
extern unsigned int frame_size;
extern vbe_mode_info_t mode_info;

extern Sprite* choose_mode;
extern Sprite* single_player;
extern Sprite* multi_player;

void draw_mode() {
  fill_screen(CREAM, current_buffer);
  draw_sprite(choose_mode, 90, 80, current_buffer); 
  draw_sprite(single_player, 85, 350, current_buffer);
  draw_sprite(multi_player, 80, 430, current_buffer);
}

