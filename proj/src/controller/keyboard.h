#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "KBC.h"

void (kbc_ih)();
int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();

//polling
int (kbd_restore)();

//process multi-byte scancodes
void (process_scancode)(uint8_t scancode);

#endif
