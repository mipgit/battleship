#include "help.h"
#include "help_view.h"
#include "graphics.h"

extern uint8_t *current_buffer;
extern unsigned int frame_size;
extern uint8_t scancode;

uint8_t *help_buffer = NULL;

void set_help_buffer() {
    if (help_buffer == NULL) {
        help_buffer = (uint8_t *)malloc(frame_size);
    }
}

void init_help() {
    set_help_buffer();
    draw_help_background(help_buffer); 
}

void help_main_loop() {
    memcpy(current_buffer, help_buffer, frame_size);
    draw_cursor(current_buffer);
    swap_buffers();
}

void help_keyboard_handler() {
    switch (scancode) {
        case SPACE_KEY: // será que isto está bem??
        case SPACE_KEY:
            set_state(ARENA);  // Return to arena
            break;
        default:
            break;
    }
}