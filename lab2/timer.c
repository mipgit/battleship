#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"


static int counter = 0;  // Global variable to count timer interrupts

int hook_id;  // Global variable for interrupt ID


int (timer_set_frequency)(uint8_t timer, uint32_t freq) { //This function adjusts the timer's frequency by configuring the control register and writing a new divisor.
  if (freq < 19 || freq > TIMER_FREQ) return 1;  // Invalid frequency

    uint16_t div = TIMER_FREQ / freq;  // Compute the divisor

    uint8_t control_word;
    if (util_sys_inb(TIMER_CTRL, &control_word) != 0) return 1;  // Read current control word
    control_word &= 0x0F;  // Keep only the 4 least significant bits (preserves timer selection)

    control_word |= TIMER_LSB_MSB | (timer << 6);  // Set LSB then MSB mode and select timer

    if (sys_outb(TIMER_CTRL, control_word) != 0) return 1;  // Write new control word

    // Write LSB and MSB of the divisor to the selected timer
    if (sys_outb(TIMER_0 + timer, div & 0xFF) != 0) return 1;  // LSB
    if (sys_outb(TIMER_0 + timer, div >> 8) != 0) return 1;  // MSB

    return 0;

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) { //This function subscribes and enables Timer 0 interrupts.

    hook_id = TIMER0_IRQ;  // Set IRQ line
    *bit_no = hook_id;  // Return the interrupt bit

    if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0) return 1;  // Subscribe
    return 0;
}

int (timer_unsubscribe_int)() { //This function unsubscribes Timer 0 interrupts.

    if (sys_irqrmpolicy(&hook_id) != 0) return 1;  // Unsubscribe
    return 0;
}


void (timer_int_handler)() { //This function handles Timer 0 interrupts. (its called on each interrupt)

    counter++;

}






int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  // confirmamos que os inputs são válidos
  if (st == NULL || timer < 0 || timer > 2) return 1;

  // construimos o nosso read-back command para ler o status do timer (temos de ativar o bit 5)
  uint8_t rb_cmd = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1); // = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer)
  
  // avisamos previamente o registo de controlo que vamos ler a config
  if (sys_outb(TIMER_CTRL, rb_cmd) != 0) return 1;

  // finalmente, lemos a config do timer, que é colocada em st
  //-> o registo do timer pretendido é obtido através de TIMER_0 + timer 
  if (util_sys_inb(TIMER_0 + timer, st)) return 1;

  return 0;
}





// já temos o valor st, que contem a config do timer (fazer timer_get_config)
// agora vamos exibir um field específico da configuração

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  // vamos ter de evocar uma funçao - já dada - para imprimir a config:
  // int timer_print_config(uint8_t timer, enum timer_status_field field, union timer_status_field_val conf)
  
  // para isso, precisamos de fazer a tradução/extração do nosso 'uint8_t st' para o formato 'union timer_status_field_val conf'
  union timer_status_field_val conf;


  switch (field) {

    // queremos o status byte (st) inteiro
    case tsf_all:  
      conf.byte = st;
      break;
    

    // queremos só os bits de inicialização -> bits 4 e 5
    case tsf_initial:  
      // fazemos uma right shift de 4 bits para colocar os bits 4-5 nas posições 0-1
      // e damos clear aos restantes bits 
      st = (st >> 4) & 0x03;
      
      // existem 4 resultados possíveis
      if (st == 1) conf.in_mode = LSB_only;  // st -> 01
      else if (st == 2) conf.in_mode = MSB_only;  // st -> 10
      else if (st == 3) conf.in_mode = MSB_after_LSB;  // st -> 11
      else conf.in_mode = INVAL_val;  // st -> 00
      
      break;


    // queremos só os bits de modo -> bits 1,2 e 3
    case tsf_mode:
      // mesmo procedimento de antes, só que agora para os bits 1, 2 e 3
      st = (st >> 1) & 0x07;

      // o valor que nos der em st é o valor do modo (verificar na tabela), 
      // EXCETO 2 casos "especiais" que devem ser mapeados:
      // 110 -> modo 2   (0b0110 <-> 6)
      // 111 -> modo 3   (0b0111 <-> 7)
      if (st == 6) conf.count_mode = 2;
      else if (st == 7) conf.count_mode = 3;
      else conf.count_mode = st;

      break;
    

    // queremos só o bit da base -> bit 0
    case tsf_base:
      conf.bcd = st & 0x01;;
      break;


    default:
      return 1;
  }
  


  // finalmente, fazemos a impressão da configuração
  if (timer_print_config(timer, field, conf) != 0) return 1;
  return 0;

}
