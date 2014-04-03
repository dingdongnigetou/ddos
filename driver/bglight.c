/*
 * (C) 2014 Jindong Huang
 *
 * driver/bglight.c
 *
 * The implement of set background light.
 *
 */

#include "bglight.h"
#include "s3c6410.h"

#define TRUE  1
#define FLASE 0 

#define TINT_CSTAT_INIMASK(n)      ((n & 0x1F))
#define TIMER3_PENDING_CLEAR       (1 << 8)
#define TIMER3_INTERRRUPT_ENABLE   (1 << 3)
#define SYS_TIMER_PRESCALER        2
#define SYS_TIMER_DIVIDER          1

#define SAMPLE_BPS  9600
#define REQ_INFO    0x60

static void set_pin_as_input()
{
	GPFCON &= ~(3 << 30);
}

static void set_pin_as_ouput()
{
	GPFCON = ((GPFCON & ~(3 << 30)) | (1 << 30));
}

static void set_pin_value(int value)
{
	if (value)
		GPFDAT |= (1 << 15);
	else
		GPFDAT &= ~(1 << 15);
}

static int get_pin_value()
{
	/* use !! to change data into 0 or 1 */
	return ( !!(GPFDAT & (1 << 15)) );
}

static void timer_init()
{
	TCNTB3 = PCLK / SYS_TIMER_PRESCALER / SYS_TIMER_DIVIDER / SAMPLE_BPS - 1; 
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER3_PENDING_CLEAR;
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER3_INTERRRUPT_ENABLE;
}

static void timer_start()
{
	TCON &= ~(1 << 16);   /* stop timer3 */
	TCON |= (1 << 17);    /* update TCNTB3 */
	TCON &= ~(1 << 17);
	/* auto reload, start timer3 */
	TCON |= ((1 << 19) | (1 << 16));
}

static void timer_stop()
{
	TCON &= ~(1 << 16);
}

static void waitTimerTick()
{
	while ((TINT_CSTAT & (1 << 8)) == 0);
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER3_PENDING_CLEAR;
}

static unsigned char crc8(unsigned v, unsigned len)
{
	unsigned char crc = 0xAC;
	while (len--){
		if ((crc & 0x80) != 0){
			crc <<= 1;
			crc ^= 0x7;
		}
		else
			crc <<= 1;
		if ((v & (1 << 31)) != 0)
			crc ^= 0x7;
		v <<= 1;
	}

	return crc;
}

static int OneWireSession(unsigned char req, unsigned char res[])
{
	unsigned  int Req;
	unsigned  *Res;
	unsigned int  i;
	Req = (req << 24) | (crc8(req << 24, 8) << 16);
	Res = (unsigned *)res;
	set_pin_value(1);
	set_pin_as_ouput();
	timer_start();
       	for (i = 0; i < 60; i++)
		waitTimerTick();

	set_pin_value(0);
	for (i = 0; i < 2; i++)
		waitTimerTick();

	for (i = 0; i < 16; i++){
		int value = !!(Req & (1 << 31));
		Req <<= 1;
		set_pin_value(value);
		waitTimerTick();
	}

	waitTimerTick();
	set_pin_as_input();
	waitTimerTick();

	for (i = 0; i < 32; i++){
		Req <<= 1;
		(*Res) |=  get_pin_value();
		waitTimerTick();
	}
	timer_stop();
	set_pin_value(1);
	set_pin_as_ouput();

	return crc8(*Res, 24) == res[0];
}

static int TryOneWireSession(unsigned char req, unsigned char res[])
{
	int i;
	for (i = 0; i < 3; i++)
		if (OneWireSession(req, res))
			return TRUE;

	return FLASE;
}

int GetInfo(unsigned char *lcd, unsigned short *firmwareVer)
{
	unsigned char res[4];

	if (!TryOneWireSession(REQ_INFO, res))
		return FLASE;

	*lcd = res[3];
	*firmwareVer = res[2] * 100 + res[1];

	return TRUE;
}

int set_bglight(unsigned char brightness) 
{
	unsigned char res[4];
	int ret;

	timer_init();

	if (brightness > 127)
		brightness = 127;
	ret = TryOneWireSession(brightness | 0x80, res);

	return ret;
}

