/*
 * (C) 2014 Jindong Huang
 *
 * include/driver/rtc.h
 */

#ifndef _RTC_H_
#define _RTC_H_

#include <types.h>

typedef struct{
	u_char year;
	u_char mon;
	u_char day;
	u_char hour;
	u_char min;
	u_char sec;
	u_char ms;
	u_char week;
}RTC_TIMER;

void rtc_timer_init();

/*
 * Hour:Min:Sec Week Mon Day, Year  
 */
void show_rtc_time();

void rtc_alarm_init(RTC_TIMER rtc);

void rtc_tick_init ();

#endif /* _RTC_H_ */

