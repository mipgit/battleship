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
  game_over = create_sprite((xpm_map_t) game_over_xpm);
  info = create_sprite((xpm_map_t) info_xpm);
  double_grid = create_sprite((xpm_map_t) grid_xpm);
  single_grid = create_sprite((xpm_map_t) single_grid_xpm);
  cursor = create_sprite((xpm_map_t) cursor_xpm);
  ship1 = create_sprite((xpm_map_t) ship1_xpm);
  ship2h = create_sprite((xpm_map_t) ship2h_xpm);
  ship2v = create_sprite((xpm_map_t) ship2v_xpm);
  ship3h = create_sprite((xpm_map_t) ship3h_xpm);
  ship3v = create_sprite((xpm_map_t) ship3v_xpm);
  ship4h = create_sprite((xpm_map_t) ship4h_xpm);
  ship4v = create_sprite((xpm_map_t) ship4v_xpm);
  player1 = create_sprite((xpm_map_t) player1_xpm);
  player1s = create_sprite((xpm_map_t) player1s_xpm);
  player2 = create_sprite((xpm_map_t) player2_xpm);
  player2s = create_sprite((xpm_map_t) player2s_xpm);
  menu_shipR = create_sprite((xpm_map_t) menu_shipR_xpm);
  menu_shipL = create_sprite((xpm_map_t) menu_shipL_xpm);
  logo = create_sprite((xpm_map_t) logo_xpm);
  sun = create_sprite((xpm_map_t) sun_xpm);
  moon = create_sprite((xpm_map_t) moon_xpm);
  cloud = create_sprite((xpm_map_t) cloud_xpm);
  star = create_sprite((xpm_map_t) star_xpm);
  ocean = create_sprite((xpm_map_t) ocean_xpm);


  if (!menu || !game_over || !info) {
    printf("Error: Failed to load one or more sprites!\n");
    return 1;
  }
  return 0;
}



void free_sprites() {
  destroy_sprite(menu);
  destroy_sprite(game_over);
  destroy_sprite(info);
  destroy_sprite(double_grid);
  destroy_sprite(single_grid);
  destroy_sprite(cursor);
  destroy_sprite(ship1);
  destroy_sprite(ship2h);
  destroy_sprite(ship2v);
  destroy_sprite(ship3h);
  destroy_sprite(ship3v);
  destroy_sprite(ship4h);
  destroy_sprite(ship4v);
  destroy_sprite(player1);
  destroy_sprite(player1s);
  destroy_sprite(player2);
  destroy_sprite(player2s);
  destroy_sprite(menu_shipR);
  destroy_sprite(menu_shipL);
  destroy_sprite(logo);
  destroy_sprite(sun);
  destroy_sprite(moon);
  destroy_sprite(cloud);
  destroy_sprite(star);
  destroy_sprite(ocean);
}


