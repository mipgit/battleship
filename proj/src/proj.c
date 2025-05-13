#include <lcom/lcf.h>
#include <lcom/vbe.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "controller/timer.h"
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/graphics.h"

#include "model/game.h"
#include "model/sprite.h"



#define FREQUENCY 60
#define TIMER 0
#define VIDEO_MODE 0x115


uint8_t kbd_irq_set;
uint8_t timer_irq_set;



int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/proj/src/debug/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/debug/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}




int start_devices() {
  if (timer_set_frequency(TIMER, FREQUENCY) != 0) {return 1;}

  if (timer_subscribe_int(&timer_irq_set) != 0) {return 1;}
  if (kbd_subscribe_int(&kbd_irq_set) != 0) {return 1;}

  if (set_frame_buffer(VIDEO_MODE) != 0) {return 1;}
  if (set_graphics_mode(VIDEO_MODE) != 0) {return 1;}

  return 0;
}


int close_devices() {
  if (kbd_unsubscribe_int() != 0) {return 1;}
  if (timer_unsubscribe_int() != 0) {return 1;}
  
  if (vg_exit() != 0) {return 1;}

  return 0;
}



int (proj_main_loop)(int argc, char *argv[]) {
  
  if (start_devices() != 0) {return 1;}
  if (load_sprites() != 0) {return 1;} //maybe create a function that loads only the initial sprites (if user exits game imm we save time)

  draw_screen();

  int ipc_status, r;
  message msg;


  while (get_state() != EXIT) { 
    
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & kbd_irq_set) { 
            game_keyboard_handler();
          }

          if (msg.m_notify.interrupts & timer_irq_set) { 
            timer_int_handler();
          }
          break;

        default:
          break; /* no other notifications expected: do nothing */	
      }
    }  
  }



  free_sprites();
  if (close_devices() != 0) {return 1;}

  return 0;
}
