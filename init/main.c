/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */

#include <s3c6410.h>
#include <unistd.h>
#include <driver/timer.h>
#include <driver/led.h>
#include <driver/lcd.h>
#include <types.h>
#include <io.h>

void led1()
{
	GPKCON0 = 0x00010000;
	GPKDAT  = 0;
}

void led2()
{
	GPKCON0 = 0x00100000;
	GPKDAT  = 0;
}

void led3()
{
	GPKCON0 = 0x01000000;
	GPKDAT  = 0;
}

void led4()
{
	GPKCON0 = 0x10000000;
	GPKDAT  = 0;
}

int main()
{	
	enirq();
	system_timer_tick(800);

	while (1){
		char c = getc();
		putc(c);
	}

	return 0;
}

