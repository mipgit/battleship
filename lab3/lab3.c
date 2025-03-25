#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "kbd_controller.h"  //we need to create the headers
#include "kbd.h"


extern uint8_t scancode;
extern uint32_t kbc_counter;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}



int(kbd_test_scan)() {

  int ipc_status, r;
  message msg;
  uint8_t irq_set;

  //we subscribe interrupt 
  if (kbd_subscribe_int(&irq_set) != 0) return 1;

  //the function is defined to run until the ESC key is pressed
  //so when we receive the breakcode for the ESC key, we must stop the loop
  while( scancode != ESC_BREAK ) { 
    
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }

    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    kbc_ih(); //we read the scancode again to check if anything changed
                              
                    bool make = !(scancode & IS_BREAK);
                    uint8_t byte_size = (scancode == 0xE0 ? 2 : 1);   //can have two bytes or 1 byte
                    kbd_print_scancode(make, byte_size, &scancode);
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
  }
  
  if(kbd_unsubscribe_int() != 0) return 1;
  if(kbd_print_no_sysinb(kbc_counter)); 
  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
