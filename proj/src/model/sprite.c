#include "sprite.h"



Sprite *create_sprite(xpm_map_t sprite) {
  
  // allocate space for the "object"
  Sprite *sp = (Sprite *) malloc(sizeof(Sprite));
  xpm_image_t img;
  
  if (sp == NULL) return NULL;
  
  // read the sprite pixmap
  sp->map = (uint32_t *) xpm_load(sprite, XPM_8_8_8_8, &img); //!!!!!!!!!!!!!!
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




int load_sprites() {
  menu = create_sprite((xpm_map_t) menu_xpm);
  arena = create_sprite((xpm_map_t) arena_xpm);
  game_over = create_sprite((xpm_map_t) game_over_xpm);
  info = create_sprite((xpm_map_t) info_xpm);
  grid = create_sprite((xpm_map_t) grid_xpm);

  if (!menu || !arena || !game_over || !info) {
    printf("Error: Failed to load one or more sprites!\n");
    return 1;
  }
  return 0;
}



void free_sprites() {
  destroy_sprite(menu);
  destroy_sprite(arena);
  destroy_sprite(game_over);
  destroy_sprite(info);
  destroy_sprite(grid);
}

