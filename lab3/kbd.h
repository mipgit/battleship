#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include <stdint.h>

void (kbc_ih)();
int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();

//por fazer -> para a função de polling
int (kbd_restore)();

#endif
