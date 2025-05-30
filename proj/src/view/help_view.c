// INCOMPLETO

#include "help_view.h"
#include "graphics.h"
#include "sprite.h"

extern Sprite* help_screen;  // Fullscreen help image
extern uint8_t *current_buffer;

void draw_help(uint8_t *buffer) {
    if (help_screen) {
        draw_sprite(help_screen, 0, 0, buffer);
    }
}