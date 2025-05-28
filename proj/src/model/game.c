#include "game.h"



GameState state = MENU;


void set_state(GameState new_state) {
  state = new_state;
}

GameState get_state() {
  return state;
}

//   MENU, // Menu initial (barquinho, farol e as cores mudam consoante a hora do dia)
//   RULES, // Regras do jogo (o que é o battleship)
//   HELP, // Help state (para o jogadro ver como se joga e atalhos do teclado)
//   MODE, // Mode selection state (when the player selects the game mode)
//   START, // Ecrã para mudar de jogador
//   ARENA, // Arena do jogo (onde o jogo acontece)
//   GAME_OVER, // Fim do jogo (quando o jogador perde)
//   EXIT, // Exit state (when the game is over and the player exits)


//   #define ESC_KEY 0x81
// #define Q_KEY 0x10
// #define SPACE_KEY 0x39
// #define M_KEY 0x32
// #define ENTER_KEY 0x1C
// #define R_KEY 0x13
// #define S_KEY 0x1F

//feito para testar os ecrãs
void game_keyboard_handler() {
  switch (scancode) {

    case M_KEY:
      set_state(MENU); //barquinho, farol e as cores mudam consoante a hora do dia
      break;
    case R_KEY:
      set_state(RULES); //regras do jogo (o que é o battleship)
      break;
    case S_KEY:
      set_state(START); //ecrã para mudar de jogador
      break;
    case ENTER_KEY:
      set_state(ARENA); //para o jogador escolher o modo de jogo
      break;
    case SPACE_KEY:
      set_state(HELP); //não esquecer de que os xpm precisam de ter uma linha a dizer "press enter fot the next screen"
      break;
    case Q_KEY:
      set_state(GAME_OVER); //pode ser preciso para testar os desenhos
      break;
    case ESC_KEY:
      set_state(EXIT);
      break;    
    default:
      break;
  }
}




void game_mouse_handler() {
  cursor_x += mouse_packet.delta_x * MOUSE_SPEED;
  cursor_y -= mouse_packet.delta_y * MOUSE_SPEED;

  if (cursor_x < 0) cursor_x = 0;
  if (cursor_x > mode_info.XResolution - cursor->width) cursor_x = mode_info.XResolution - cursor->width;
  if (cursor_y < 0) cursor_y = 0;
  if (cursor_y > mode_info.YResolution - cursor->height) cursor_y = mode_info.YResolution - cursor->height;  
}




void help_main_loop() {
  draw_info();
  draw_cursor(current_buffer);
  swap_buffers();
}

void game_over_main_loop() {
  draw_game_over();
  draw_cursor(current_buffer);
  swap_buffers();
}


void free_buffers() {
  free_buffer(current_buffer);
  free_buffer(arena_buffer);
  free_buffer(menu_buffer);
  free_buffer(rules_buffer);
}

