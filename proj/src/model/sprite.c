#include "sprite.h"



Sprite *create_sprite(xpm_map_t sprite) {
  
  // allocate space for the "object"
  Sprite *sp = (Sprite *) malloc(sizeof(Sprite));
  xpm_image_t img;
  
  if (sp == NULL) return NULL;
  
  // read the sprite pixmap
  sp->map = xpm_load(sprite, XPM_INDEXED, &img);
  if (sp->map == NULL) {
    free(sp);
    return NULL;
  }

  sp->width = img.width;
  sp->height = img.height;
  //...

  return sp;
}

void destroy_sprite(Sprite *sp) {
  if (sp == NULL) return;
  if (sp->map) free(sp->map);
  free(sp); 
  sp = NULL; 
}




void load_sprites() {
  menu = create_sprite((xpm_map_t) pic11);
  arena = create_sprite((xpm_map_t) pic21);
  game_over = create_sprite((xpm_map_t) pic31);
  info = create_sprite((xpm_map_t) cross1);
}



void free_sprites() {
  destroy_sprite(menu);
  destroy_sprite(arena);
  destroy_sprite(game_over);
  destroy_sprite(info);
}

