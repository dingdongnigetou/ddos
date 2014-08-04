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

	BCDYEAR = 0x0E;
	BCDMON  = 0x07;
	BCDDATE = 0x28;
	BCDDAY  = 0x01;
	BCDHOUR = 0x20;
	BCDMIN  = 0x32;
	BCDSEC  = 0x50;

	RTCCON &= ~0x01;
}

static char table[] = 
{
	0x30, 0x31, 0x32, 0x33, 0x34, 
	0x35, 0x36, 0x37, 0x38, 0x39
};
static char week[8][3] = 
{
	"DEF", "MON", "TUE", "WED", 
	"THU", "FRI", "STU", "SUN"
};

void show_rtc_time()
{
	RTCCON |= 0x01;

	u_char year, mon, date, day, hour, min, sec;

	year = BCDYEAR & 0xff;
	mon  = BCDMON  & 0x1f;
	date = BCDDATE & 0x3f;
	day  = BCDDAY  & 0x07;
	hour = BCDHOUR & 0x3f;
	min  = BCDMIN  & 0x7f;
	sec  = BCDSEC  & 0x7f;

	putc(' ');
	putc(table[2]);
	putc(table[0]);
	putc(table[1]);
	putc(table[4]);
	putc('-');
	putc(table[mon >> 4]);
	putc(table[mon & 0x0f]);
	putc('-');
	putc(table[date >> 4]);
	putc(table[date & 0x0f]);

	putc(' ');
	putc(week[day & 0x0f][0]);
	putc(week[day & 0x0f][1]);
	putc(week[day & 0x0f][2]);

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

