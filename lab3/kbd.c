#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "kbd.h"
#include "kbd_controller.c"

uint8_t scancode = 0;
int kbd_hook_id = 1;


//retrieves the scancode
void (kbc_ih)() {
    if(read_KBC_output(KBC_WRITE_CMD, &scancode) != 0) {printf("Error reading scancode\n"); return;}
}


int(kbd_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(kbd_hook_id);
    if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id) != 0) return 1;
    return 0;
}


int (kbd_unsubscribe_int)() {
    if (sys_irqrmpolicy(&kbd_hook_id) != 0) return 1;
    return 0;
}
