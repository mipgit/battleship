#include "start_view.h"

extern uint8_t *current_buffer;
extern uint8_t *start_buffer;
extern unsigned int frame_size;

extern Sprite *logo;
extern Sprite *start_option;
extern Sprite *rules_option;
extern Sprite *help_option;




void draw_start_background(uint8_t *buffer) {
  fill_screen(TEAL, buffer);
  draw_sprite(logo, 5, 55, buffer);
}


void draw_start() {
  memcpy(current_buffer, start_buffer, frame_size);
  draw_start_options(current_buffer);
}


void draw_start_options(uint8_t *buffer) {

  StartOption selected_option = get_start_option();
    
    if (selected_option == GO_START) {
        draw_sprite_recolor(start_option, OPTIONS_X, OPTION_START_Y, HOVER_COLOR, buffer);
    } else {
        draw_sprite(start_option, OPTIONS_X, OPTION_START_Y, buffer);
    }
    
    
    if (selected_option == GO_RULES) {
        draw_sprite_recolor(rules_option, OPTIONS_X, OPTION_RULES_Y, HOVER_COLOR, buffer);
    } else {
        draw_sprite(rules_option, OPTIONS_X, OPTION_RULES_Y, buffer);
    }
    

    if (selected_option == GO_HELP) {
        draw_sprite_recolor(help_option, OPTIONS_X, OPTION_HELP_Y, HOVER_COLOR, buffer);
    } else {
        draw_sprite(help_option, OPTIONS_X, OPTION_HELP_Y, buffer);
    }
}


