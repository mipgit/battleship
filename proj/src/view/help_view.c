#include "help_view.h"

extern Sprite* logo;  


void draw_help(uint8_t *buffer) {
    fill_screen(WHITE, buffer);
    draw_sprite(logo, 5, 100, buffer);
}
