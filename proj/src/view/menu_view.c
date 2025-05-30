#include "menu_view.h"

extern uint8_t *current_buffer;
extern uint8_t *menu_buffer;
extern unsigned int frame_size;
extern vbe_mode_info_t mode_info;

extern Sprite *menu_shipR;
extern Sprite *menu_shipL;
extern Sprite *logo;
extern Sprite *sun; 
extern Sprite *moon;

#define DAY_START_HOUR 7
#define DAY_END_HOUR 18
#define DAY_END_MINUTE 30
#define LIGHT_BLUE 0x8DBCC7 
#define DARK_BLUE  0x213448 

void draw_menu_background(uint8_t *buffer) {
    if (read_rtc_time() != 0) {
        return;
    }

    printf("Current time: %02d:%02d\n", rtc_info.hours, rtc_info.minutes);

    uint32_t background;
    Sprite *sky;
    if (daytime(rtc_info.hours, rtc_info.minutes)) {
        background = LIGHT_BLUE; 
        sky = sun; 
    } else {
        background = DARK_BLUE;
        sky = moon;
    }

    fill_screen(background, buffer);
    draw_sprite(logo, 5, 130, buffer);
    draw_sprite(sky, 40, 20, buffer);

}

bool daytime(uint8_t hour, uint8_t minute) {
  return (hour > DAY_START_HOUR && (hour < DAY_END_HOUR || (hour == DAY_END_HOUR && minute < DAY_END_MINUTE)));
}


void draw_menu() {
  memcpy(current_buffer, menu_buffer, frame_size);

  static int x = 0;
  static int dx = 2;
  int y = 400 - menu_shipR->height / 2;

  x += dx;
  if (x < 0) {
    x = 0;
    dx = -dx;
  }
  if (x > (int)(mode_info.XResolution - menu_shipR->width)) {
    x = mode_info.XResolution - menu_shipR->width;
    dx = -dx;
  }

  Sprite *sprite_to_draw = (dx > 0) ? menu_shipR : menu_shipL;
  draw_sprite(sprite_to_draw, x, y, current_buffer);
}


