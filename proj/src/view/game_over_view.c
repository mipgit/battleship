#include "game_over_view.h"

extern uint8_t *current_buffer;
extern uint8_t *game_over_buffer;
extern unsigned int frame_size;
extern vbe_mode_info_t mode_info;

extern Sprite *game_over;
extern Sprite *menu_option;
extern Sprite *exit_option;



void draw_game_over_background(uint8_t *buffer) {

    fill_screen(0x000080, buffer); // Dark blue background
    
    if (game_over != NULL) {
        draw_sprite(game_over, (mode_info.XResolution - game_over->width) / 2, 50, buffer);
    }
    
    draw_game_over_options(buffer);
}

void draw_game_over_options(uint8_t *buffer) {
    GameOverOption selected = get_game_over_option();
    
    if (menu_option != NULL) {
        if (selected == GO_MENU) {
            draw_sprite_highlighted(menu_option, OPTIONS_X, OPTION_MENU_Y, buffer);
        } else {
            draw_sprite(menu_option, OPTIONS_X, OPTION_MENU_Y, buffer);
        }
    }
    
    if (exit_option != NULL) {
        if (selected == GO_EXIT) {
            draw_sprite_highlighted(exit_option, OPTIONS_X, OPTION_EXIT_Y, buffer);
        } else {
            draw_sprite(exit_option, OPTIONS_X, OPTION_EXIT_Y, buffer);
        }
    }

    if (selected == GO_MENU) {
      draw_string("->", OPTIONS_X - ARROW_OFFSET, OPTION_MENU_Y + (menu_option->height / 2) - 8, 0xFFFFFF);
    } else {
      draw_string("->", OPTIONS_X - ARROW_OFFSET, OPTION_EXIT_Y + (exit_option->height / 2) - 8, 0xFFFFFF);
    }
}

void draw_game_over_screen() {
    memcpy(current_buffer, game_over_buffer, frame_size);
    
    draw_game_over_options(current_buffer);
}
