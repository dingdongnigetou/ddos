/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd/bg_light.c
 *
 * The implement of set background light.
 *
 */

#include <s3c6410.h>
#include <common.h>
#include <types.h>
#include <driver/bg_light.h>
#include <driver/pwm.h>

static u_char crc8(u_int v, u_int len)
{
	u_char crc = 0xAC;
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

static int OneWireSession(u_char req, u_char res[])
{
	u_int Req;
	u_int *Res;
	u_int i;

	Req = (req << 24) | (crc8(req << 24, 8) << 16);
	Res = (u_int *)res;
	GPFDAT |= (1 << 15); /* set 1 */
	/* set pin as output */
	GPFCON = ((GPFCON & ~(3 << 30)) | (1 << 30));

	timer_start();

       	for (i = 0; i < 60; i++)
		waitTimerTick();

	GPFDAT &= ~(1 << 15); /* set 0 */

	for (i = 0; i < 2; i++)
		waitTimerTick();

	for (i = 0; i < 16; i++){
		int value = !!(Req & (1 << 31));
		Req <<= 1;
		if (value)
			GPFDAT |= (1 << 15); 
		else
			GPFDAT &= ~(1 << 15); 
		waitTimerTick();
	}

	waitTimerTick();
	GPFCON &= ~(3 << 30); /* set pin as input */
	waitTimerTick();

	for (i = 0; i < 32; i++){
		Req <<= 1;
		(*Res) |= (!!(GPFDAT & (1 << 15)));
		waitTimerTick();
	}

	timer_stop();
	GPFDAT |= (1 << 15); 
	/* set pin as output */
	GPFCON = ((GPFCON & ~(3 << 30)) | (1 << 30));

	return crc8(*Res, 24) == res[0];
}

static int TryOneWireSession(u_char req, u_char res[])
{
	int i;
	for (i = 0; i < 3; i++)
		if (OneWireSession(req, res))
			return TRUE;

	return FALSE;
}

int set_bglight(u_char brightness) 
{
	u_char res[4];
	int ret;

	timer_init();

	if (brightness > 127)
		brightness = 127;
	ret = TryOneWireSession(brightness | 0x80, res);

	return ret;
}

