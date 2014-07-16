/*
 * (C) 2014 Jindong Huang
 *
 * driver/rtc.c
 */

#include <s3c6410.h>
#include <driver/rtc.h>
#include <types.h>
#include <io.h>

/* call once only */
void rtc_timer_init()
{
	RTCCON |= 0x01;

	BCDHOUR = 0x22;
	BCDMIN  = 0x14;
	BCDSEC  = 0x50;

	RTCCON &= ~0x01;
}

void show_rtc_time()
{
	char table[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

	RTCCON |= 0x01;

	u_char hour, min, sec;

	hour = BCDHOUR & 0x3f;
	min  = BCDMIN  & 0x7f;
	sec  = BCDSEC  & 0x7f;

	putc(' ');
	putc(table[hour >> 4]);
	putc(table[hour & 0x0f]);
	putc(':');
	putc(table[min >> 4]);
	putc(table[min & 0x0f]);
	putc(':');
	putc(table[sec >> 4]);
	putc(table[sec & 0x0f]);
	putc('\n');

	RTCCON &= ~0x01;
}

