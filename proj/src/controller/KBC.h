#ifndef KBC_H
#define KBC_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int (read_KBC_status)(uint8_t* status);
int (read_KBC_output)(uint8_t port, uint8_t *output);
int (write_KBC_cmd)(uint8_t port, uint8_t commandByte);

#endif 
