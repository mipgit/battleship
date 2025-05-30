// INCOMPLETO

#include "rules_view.h"
#include "graphics.h"
#include "sprite.h"

extern Sprite* rules_screen;  // Fullscreen rules image
extern uint8_t *current_buffer;

void draw_rules_background(uint8_t *buffer) {
    fill_screen(RULES_BG_COLOR, buffer);
    
    if (rules_screen) {
        // Center the rules content - rules is a much smaller xpm
        uint16_t x = (mode_info.XResolution - rules_screen->width) / 2;
        uint16_t y = (mode_info.YResolution - rules_screen->height) / 3;
        draw_sprite(rules_screen, x, y, buffer);
    }
}

void draw_rules() {
    if (rules_screen) {
        draw_sprite(rules_screen, 0, 0, current_buffer);
    }
}