#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <stdbool.h>

#include "i8042.h"
#include "KBC.h"


extern struct packet pp;
extern int byte_index;
extern bool ready;


int (mouse_subscribe_int) (uint8_t* bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();

int (mouse_write_cmd)(uint8_t command);

int (_mouse_enable_data_reporting)();
int (_mouse_disable_data_reporting)();

bool (mouse_sync_bytes)();

void (create_packet)(uint8_t mouse_bytes[3], struct packet mouse_packet);


#endif /* _MOUSE_H_ */
