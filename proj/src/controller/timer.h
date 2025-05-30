#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>
#include <lcom/timer.h> 
#include <stdint.h>
#include "i8254.h"


int (timer_subscribe_int)(uint8_t *bit_no);
int (timer_unsubscribe_int)();
int (timer_get_conf)(uint8_t timer, uint8_t *st);
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

#endif
