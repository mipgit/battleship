#include "sprite_view.h"


int(draw_sprite)(Sprite *sprite, uint16_t x, uint16_t y, uint8_t *buffer) {
  
  int height = sprite->height;
  int width = sprite->width;
  uint32_t color;
  
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      color = sprite->map[i * width + j];
      if (color == xpm_transparency_color(XPM_8_8_8_8)) continue; // skiping transparent pixels
      if (draw_pixel(x + j, y + i, color, buffer) != 0) return 1; 
    }
  }
  return 0;
}


int draw_sprite_recolor(Sprite *sprite, uint16_t x, uint16_t y, uint32_t recolor, uint8_t *buffer) {
  
  int height = sprite->height;
  int width = sprite->width;
  uint32_t color;
  
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      color = sprite->map[i * width + j];
      if (color == xpm_transparency_color(XPM_8_8_8_8)) continue; 
      if (draw_pixel(x + j, y + i, recolor, buffer) != 0) return 1; 
    }
  }
  return 0;
}


