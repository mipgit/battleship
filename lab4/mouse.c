#include "mouse.h"


int mouse_hook_id = 12; 

struct packet pp;
int byte_index;
bool ready;



//diff from what we've been doing!!!! had to change it because of mouse_irq_set!!!
int (mouse_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = mouse_hook_id; //!!!!
    if (sys_irqsetpolicy(MOUSE_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &mouse_hook_id) != 0) return 1;
    return 0;
}

int (mouse_unsubscribe_int)() {
    if (sys_irqrmpolicy(&mouse_hook_id) != 0) return 1;
    return 0;
}





/*
-> summary of actions for sending cmd to mouse
-> see https://pages.up.pt/~up722898/aulas/lcom2425/lab4/lab4_3.html

1) request fowarding of byte (cmd) to the mouse -> write KBC_WRITE_MOUSE (0xD4) to port KBC_CMD_REG (0x64)
2) write command (one of these below) to KBC_ARGS (0x60)
3) read acknowledgment byte received from the mouse from OUT_BUF (0x60)   (if success, the ack byte is MOUSE_OK (0xFA), if error 0xFE)
4) if cmd has arguments, we repeat the 3 previous steps for each byte of the argument(s)  (if 0xFE earlier, we resend the entire cmd from the beggining, not only the last byte)
---- mouse executes cmd ----
5) if cmd has response, we read it from OUT_BUF (0x60) 
*/

int (mouse_write_cmd)(uint8_t command) {
    
    int timeout = 0;

    while (timeout < 3) {
        if (write_KBC_cmd(KBC_CMD_REG, KBC_WRITE_MOUSE) != 0) {
            printf("Error writing to KBC_CMD_REG.\n");
            return 1;}
        if (write_KBC_cmd(KBC_ARGS, command) != 0) {
            printf("Error writing to KBC_ARGS.\n");
            return 1;}
        
        tickdelay(micros_to_ticks(DELAY_US));
        
        uint8_t mouse_response;
        //if (read_KBC_output(OUT_BUF, &mouse_response, 1) != 0) {
        //    printf("Error reading from OUT_BUF.\n");
        //    return 1;}
        
        if (util_sys_inb(OUT_BUF, &mouse_response) != 0) {
            printf("Error reading from OUT_BUF.\n");
            return 1;}

        if (mouse_response == MOUSE_ACK) return 0;
        timeout++;
    }
    
    return 1; 
}




int (_mouse_enable_data_reporting)() {
    if (mouse_write_cmd(MOUSE_ENABLE) != 0) {
        printf("Error enabling data reporting.\n");
        return 1;
    }
    return 0;
}

int (_mouse_disable_data_reporting)() {
    if (mouse_write_cmd(MOUSE_DISABLE) != 0) {
        printf("Error disabling data reporting.\n");
        return 1;
    }
    return 0;
}




void (mouse_ih)() {

    uint8_t st;
    uint8_t current_byte;


    if (read_KBC_status(&st) != 0) {
        printf("Error reading status.\n");
        return;
    }


    if (st & OBF && !(st & (PARITY | TIMEOUT))) {

        //we read a byte from the OUT_BUF 
        if (read_KBC_output(OUT_BUF, &current_byte, 1) != 0) {
            printf("Error reading from OUT_BUF.\n");
            return;
        }


        /*check for sync:
        imagine we are processing the 1st byte of the packet (index=0)
        the 1st byte of the packet is the control byte
        a valid control byte must have its 3 bit set 
        that's what we're checking here 
        */
        if (byte_index == 0 && !(current_byte & IS_FIRST_BYTE)) {
            printf("Invalid byte!\n");
            return;
        }


        //we store the byte on the packet
        pp.bytes[byte_index] = current_byte; 


        //depeding on the byte, we store diff information (see slide 4)
        switch (byte_index) {
            case 0:
                pp.lb = current_byte & MOUSE_LB;
                pp.rb = current_byte & MOUSE_RB;
                pp.mb = current_byte & MOUSE_MB;
                pp.x_ov = current_byte & MOUSE_X_OVERFLOW;
                pp.y_ov = current_byte & MOUSE_Y_OVERFLOW;
                break;

            case 1:
                pp.delta_x = current_byte;
                if (pp.bytes[0] & MOUSE_MSB_X_DELTA) {
                    pp.delta_x |= 0xFF00;
                }
                break;

            case 2:
                pp.delta_y = current_byte;
                if (pp.bytes[0] & MOUSE_MSB_Y_DELTA) {
                    pp.delta_y |= 0xFF00;
                }
                break;
        }

        //we move to the next byte
        byte_index++; 
        

        //if we reach index=3 it means we have processed 3 bytes and therefore completed a packet
        if (byte_index == 3) {
            byte_index = 0; //we reset index for the next packet
            ready = true; //set ready to true to indicate that a complete packet has been received
        }

    }
    
}

