#include "rules_view.h"

extern Sprite* rules_content;  


void draw_rules(uint8_t *buffer) {
    fill_screen(WHITE, buffer);
    
    uint16_t x = (mode_info.XResolution - rules_content->width) / 2;
    uint16_t y = (mode_info.YResolution - rules_content->height) / 3;
    draw_sprite(rules_content, x, y, buffer);
}

