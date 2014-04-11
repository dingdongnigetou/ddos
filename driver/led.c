/*
 * (C) 2014 JinDongHuang
 *
 * driver/led.c
 *
 * The implement of led driver device.
 *
 */

#include "s3c6410.h"

void delay()
{
	int i, j;
	for (i = 0;i < 50;i++)
		for (j = 0;j < 100;j++);
}

void ledone_flicker()
{
	GPKCON0 = 0x00010000; 
	GPKDAT  = 0;
	delay();
	GPKDAT  = 0xFFFFFFFF;
	delay();
}

