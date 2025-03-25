#ifndef _LCOM_KBD_CONTROLLER_H_
#define _LCOM_KBD_CONTROLLER_H_


#include "stdint.h"

int (read_KBC_status)(uint8_t* status);
int (write_KBC_command)(uint8_t port, uint8_t commandByte);
int (read_KBC_output)(uint8_t port, uint8_t *output);


#endif 
