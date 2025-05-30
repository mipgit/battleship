#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "controller/timer.h"
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/graphics.h"

#include "view/game_view.h"

#include "model/game_macro.h"


typedef enum {
  MENU, // Menu initial (barquinho, farol e as cores mudam consoante a hora do dia)
  RULES, // Regras do jogo (o que é o battleship)
  HELP, // Help state (para o jogadro ver como se joga e atalhos do teclado)
  MODE, // Mode selection state (when the player selects the game mode)
  START, // Ecrã para mudar de jogador
  ARENA, // Arena do jogo (onde o jogo acontece)
  GAME_OVER, // Fim do jogo (quando o jogador perde)
  EXIT, // Exit state (when the game is over and the player exits)
} GameState;


extern uint8_t scancode;

extern uint8_t byte_index;
extern struct packet mouse_packet;
int cursor_x;
int cursor_y;

extern vbe_mode_info_t mode_info;
extern uint8_t *current_buffer;
extern uint8_t *arena_buffer;
extern uint8_t *menu_buffer;
extern uint8_t *rules_buffer;
extern uint8_t *help_buffer;
extern uint8_t *game_over_buffer;
extern uint8_t *start_buffer;
extern uint8_t *mode_buffer;



extern GameState state;

void set_state(GameState new_state);
GameState get_state();

void game_timer_handler();
void game_keyboard_handler();
void game_mouse_handler();



void free_buffers();

#endif
