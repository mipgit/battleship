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
  info = create_sprite((xpm_map_t) info_xpm);
  double_grid = create_sprite((xpm_map_t) grid_xpm);
  single_grid = create_sprite((xpm_map_t) single_grid_xpm);
  cursor = create_sprite((xpm_map_t) cursor_xpm);
  bomb = create_sprite((xpm_map_t) bomb_xpm);
  ship1 = create_sprite((xpm_map_t) ship1_xpm);
  ship2h = create_sprite((xpm_map_t) ship2h_xpm);
  ship2v = create_sprite((xpm_map_t) ship2v_xpm);
  ship3h = create_sprite((xpm_map_t) ship3h_xpm);
  ship3v = create_sprite((xpm_map_t) ship3v_xpm);
  ship4h = create_sprite((xpm_map_t) ship4h_xpm);
  ship4v = create_sprite((xpm_map_t) ship4v_xpm);
  player1 = create_sprite((xpm_map_t) player1_xpm);
  player2 = create_sprite((xpm_map_t) player2_xpm);
  menu_shipR = create_sprite((xpm_map_t) menu_shipR_xpm);
  menu_shipL = create_sprite((xpm_map_t) menu_shipL_xpm);
  logo = create_sprite((xpm_map_t) logo_xpm);
  game_over = create_sprite((xpm_map_t) game_over_xpm);
  if (game_over == NULL) return 1;
  menu_option = create_sprite((xpm_map_t) menU_xpm);  // o u está maiúsculo pq estava a dar erro
  exit_option = create_sprite((xpm_map_t) exit_xpm);
  choose_mode = create_sprite((xpm_map_t) mode_xpm);
  single_player = create_sprite((xpm_map_t) single_player_xpm);
  multi_player = create_sprite((xpm_map_t) multi_player_xpm);
  setup = create_sprite((xpm_map_t) setup_xpm);
  return 0;
}



void free_sprites() {
  destroy_sprite(game_over);
  destroy_sprite(info);
  destroy_sprite(double_grid);
  destroy_sprite(single_grid);
  destroy_sprite(cursor);
  destroy_sprite(bomb);
  destroy_sprite(ship1);
  destroy_sprite(ship2h);
  destroy_sprite(ship2v);
  destroy_sprite(ship3h);
  destroy_sprite(ship3v);
  destroy_sprite(ship4h);
  destroy_sprite(ship4v);
  destroy_sprite(player1);
  destroy_sprite(player2);
  destroy_sprite(menu_shipR);
  destroy_sprite(menu_shipL);
  destroy_sprite(logo);
  destroy_sprite(menu_option);
  destroy_sprite(exit_option);
  destroy_sprite(choose_mode);
  destroy_sprite(single_player);
  destroy_sprite(multi_player);
  destroy_sprite(setup);
}

