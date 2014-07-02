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

#define MEM_SYS_CFG        (*(volatile unsigned long *)0x1E00F120)
#define NFCONF             (*(volatile unsigned long *)0x10200000)
#define NFCONT             (*(volatile unsigned long *)0x10200004)
#define NFCMMD             (*(volatile unsigned long *)0x10200008)
#define NFADDR             (*(volatile unsigned long *)0x1020000C)
#define NFDATA             (*(volatile unsigned char *)0x10200010)
#define NFSTAT             (*(volatile unsigned long *)0x10200028)


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
//	enirq();
//	system_timer_tick(800);


	led3();
	u_char buf[10] = "hello";

//	nand_write(0x51000000, buf, 10);
	nand_read(0xC1000000, buf, 10);
	puts(buf);


	while (1){
//		led2();
//		system_wait_timer_tick();
//		led3();
//		system_wait_timer_tick();
	}

	return 0;
}

