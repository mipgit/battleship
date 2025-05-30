// INCOMPLETO

#include "rules_view.h"

extern Sprite* rules_content;  


void draw_rules(uint8_t *buffer) {
    fill_screen(LILAC, buffer);
    
    // Draw the rules_option at the top
    uint16_t option_x = (mode_info.XResolution - rules->width) / 2;
    uint16_t option_y = 30; // Position at top with some margin
    draw_sprite(rules, option_x, option_y, buffer);
    
    // Draw the rules_text below
    uint16_t text_x = (mode_info.XResolution - rules_text->width) / 2;
    uint16_t text_y = option_y + rules->height + 20; // Add some spacing
    draw_sprite(rules_text, text_x, text_y, buffer);
}

