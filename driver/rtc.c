/*
 * (C) 2014 Jindong Huang
 *
 * driver/rtc.c
 */

#include <s3c6410.h>
#include <driver/rtc.h>
#include <types.h>
#include <io.h>

static u_char bin_to_bcd(u_char bin)
{
	u_char bcd;

	bcd  = (bin / 10);
	bcd |= (bin % 10);

	return bcd;
}

static u_char bcd_to_bin(u_char bcd)
{
	u_char temp;

	temp = 10 * (bcd & 0xf0);
	temp += (bcd & 0x0f);

	return temp;
}

static void turn_bin_bcd(RTC_TIMER rtc_d, RTC_TIMER rtc_s)
{
	rtc_d.year = bin_to_bcd(rtc_s.year);
	rtc_d.mon  = bin_to_bcd(rtc_s.mon);
	rtc_d.day  = bin_to_bcd(rtc_s.day);
	rtc_d.hour = bin_to_bcd(rtc_s.hour);
	rtc_d.min  = bin_to_bcd(rtc_s.min);
	rtc_d.sec  = bin_to_bcd(rtc_s.sec);
	rtc_d.week = bin_to_bcd(rtc_s.week);
}


static void put_to_reg(RTC_TIMER rtc)
{
	BCDYEAR = rtc.year;
	BCDMON  = rtc.mon;
	BCDDAY  = rtc.day;
	BCDDATE = rtc.week;
	BCDHOUR = rtc.hour;
	BCDMIN  = rtc.min;
	BCDSEC  = rtc.sec;
}

static RTC_TIMER def_rtc = {0, 0, 0, 0, 0, 0, 0};

void rtc_timer_init()
{
	RTCCON |= 0x01;

	RTC_TIMER rtc;
	turn_bin_bcd(rtc, def_rtc);
	put_to_reg(rtc);

	RTCCON &= ~0x01;
}

static RTC_TIMER rtc_read_timer()
{
	RTCCON |= 0x01;

	RTC_TIMER rtc;
	rtc.year = bcd_to_bin(BCDYEAR);
	rtc.mon  = bcd_to_bin(BCDMON);
	rtc.day  = bcd_to_bin(BCDDAY);
	rtc.week = bcd_to_bin(BCDDATE);
	rtc.hour = bcd_to_bin(BCDHOUR);
	rtc.min  = bcd_to_bin(BCDMIN);
	rtc.sec  = bcd_to_bin(BCDSEC);

	RTCCON &= ~0x01;

	return rtc;
}

static char table[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

void show_rtc_time()
{
	RTC_TIMER rtc; //= rtc_read_timer();

//	putc(table[(rtc.hour >> 4) & 0xf]);
//	putc(table[rtc.hour & 0xf]);
//	putc(':');
//	putc(table[(rtc.min >> 4) & 0xf]);
//	putc(table[rtc.min & 0xf]);
//	putc(':');
//	putc(table[(rtc.sec >> 4) & 0xf]);
//	putc(table[rtc.sec & 0xf]);
	putc('\n');
}

