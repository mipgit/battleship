#include <lcom/lcf.h>
#include <lcom/lab2.h>
#include <lcom/timer.h>

#include <stdbool.h>
#include <stdint.h>


int main(int argc, char *argv[]) {

  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t config;                                          // vamos colocar aqui a configuração do timer
  if (timer_get_conf(timer, &config)) return 1;            // chamamos função que lê a configuração do timer e coloca-a em config
  if (timer_display_conf(timer, config, field)) return 1;   // chamamos a função que dá display da configuração
  return 0;           
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(timer_test_int)(uint8_t time) {

    int ipc_status;
    message msg;
    int r;
    uint8_t bit_no;
    int irq_set;
    
    if (timer_subscribe_int(&bit_no) != 0) return 1;  // Subscribe to timer interrupts
    irq_set = BIT(bit_no);  // Create the interrupt mask

    counter = 0;  // Reset the global counter

    int ticks_per_second = sys_hz();  // Get the system's tick rate

    while (counter < time * ticks_per_second) {  // Run for the given number of seconds
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {  // Wait for a message
            printf("driver_receive failed with: %d\n", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {  // Check if it's a hardware interrupt notification
            if (_ENDPOINT_P(msg.m_source) == HARDWARE) {
                if (msg.m_notify.interrupts & irq_set) {
                    timer_int_handler();  // Handle the timer interrupt

                    if (counter % ticks_per_second == 0) {
                        printf("One second has passed.\n");
                    }
                }
            }
        }
    }

    if (timer_unsubscribe_int() != 0) {
      return 1; }

    return 0;

}
