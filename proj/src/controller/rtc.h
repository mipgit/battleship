#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

struct real_time_clock_info{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};


struct real_time_clock_info rtc_info;
uint8_t output;

int read_rtc_time();
int read_rtc_output(uint8_t command, uint8_t *output);
uint8_t to_binary(uint8_t bcd_value);
int is_rtc_binary();

int rtc_subscribe_int(uint8_t *bit_no);
int rtc_unsubscribe_int();
int rtc_enable_update_int();
void rtc_ih();

#endif

