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
#include <timer.h>
#include <led.h>
#include <lcd.h>
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
	user_timer_tick(800);

	while (1){
		led2();
		user_wait_timer_tick();
		led3();
		user_wait_timer_tick();
	}

	return 0;
}

