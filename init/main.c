/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include "s3c6410.h"
#include "serial.h"
#include <stdio.h>

void delay()
{
	int i, j;
	for (i = 0;i < 50;i++)
		for (j = 0;j < 100;j++);
}

int main(void)
{

	GPKCON0 = 0x00010000; 
	uart0_init();

	while(1)
	{

		unsigned char ch;
		ch = uart0_getc();
		uart0_putc(3);

			GPKDAT = 0;
			delay();
			GPKDAT = 0xFFFFFFFF;
			delay();
	}

	return 0;
}

