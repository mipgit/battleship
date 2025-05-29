#include "controller/rtc.h"

int read_rtc_output(uint8_t command, uint8_t *output) {
    if (sys_outb(0x70, command) != 0) {return 1;}
    if (util_sys_inb(0x71, output) != 0) {return 1;}
    
    return 0;
}

uint8_t to_binary(uint8_t bcd_value) {
    return ((bcd_value >> 4) * 10) + (bcd_value & 0xF);
}

int is_rtc_binary() {
    uint8_t status;
    if (read_rtc_output(11, &status)) {
        return 1;
    }
    return status & BIT(2);
}

int read_rtc_time() {
    uint8_t output;
    int is_binary = is_rtc_binary();

    if (read_rtc_output(4, &output)) {return 1;}
    rtc_info.hours = is_binary ? output : to_binary(output);

    if (read_rtc_output(2, &output)) {return 1;}
    rtc_info.minutes = is_binary ? output : to_binary(output);

    return 0;
}
