#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_hook_id; //this will identify our program's subscription to an IRQ line (so that the kernel can track/manage interrupt subscriptions)
int timer_counter = 0; //used to count the number of interrupts --- see lab2.c



int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;    
  timer_hook_id = *bit_no;  
  if (sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE, &timer_hook_id) != 0) return 1;  
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timer_hook_id) != 0) return 1;
  return 0;
}

void (timer_int_handler)() {
  timer_counter++;
}




int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL || timer < 0 || timer > 2) return 1;
  uint8_t rb_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer); 
  if (sys_outb(TIMER_CTRL, rb_cmd) != 0) return 1;
  if (util_sys_inb(TIMER_0 + timer, st)) return 1;
  return 0;
}



int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  union timer_status_field_val conf;


  switch (field) {

    // queremos o status byte (st) inteiro
    case tsf_all:  
      conf.byte = st;
      break;
    

    // queremos só os bits de inicialização -> bits 4 e 5
    case tsf_initial:  
      st = (st >> 4) & 0x03;
      if (st == 1) conf.in_mode = LSB_only;  // st -> 01
      else if (st == 2) conf.in_mode = MSB_only;  // st -> 10
      else if (st == 3) conf.in_mode = MSB_after_LSB;  // st -> 11
      else conf.in_mode = INVAL_val;  // st -> 00
      break;


    // queremos só os bits de modo -> bits 1,2 e 3
    case tsf_mode:
      st = (st >> 1) & 0x07;
      if (st == 6) conf.count_mode = 2;
      else if (st == 7) conf.count_mode = 3;
      else conf.count_mode = st;
      break;
    

    case tsf_base:
      conf.bcd = st & 0x01;;
      break;


    default:
      return 1;
  }
  

  if (timer_print_config(timer, field, conf) != 0) return 1;
  return 0;
}




int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  //validate inputs
  if (freq < 19 || freq > TIMER_FREQ || timer < 0 || timer > 2) return 1;


  /*part 1*/
  uint8_t rb_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer + 1);
  if (sys_outb(TIMER_CTRL, rb_cmd) != 0) return 1;

  uint8_t old_conf, new_conf;
  timer_get_conf(timer, &old_conf);

  //-> new configuration:

  //timer selection (7,6)
  uint8_t selectedTimer;

  switch(timer) {
      case 0: 
        new_conf |= TIMER_SEL0; 
        selectedTimer = TIMER_0;
        break;
      
      case 1: 
        new_conf |= TIMER_SEL1; 
        selectedTimer = TIMER_1;
        break;
      
      case 2: 
        new_conf |= TIMER_SEL2;
        selectedTimer = TIMER_2;
        break;
      
      default: 
        return 1;
  }

  //register selection (5,4)
  new_conf |= TIMER_LSB_MSB;

  //we keep mode and BCD/binary (3,2,1,0)
  new_conf = old_conf & 0x0F;


  /*part 2*/
  uint16_t counter = TIMER_FREQ / freq; 
  uint8_t LSB, MSB;
  util_get_LSB(counter, &LSB);
  util_get_MSB(counter, &MSB);


  if (sys_outb(TIMER_CTRL, new_conf) != 0) return 1;

  if (sys_outb(selectedTimer, LSB) != 0) return 1;
  if (sys_outb(selectedTimer, MSB) != 0) return 1;

  return 0;
}

