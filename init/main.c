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

int main(void)
{
	GPKCON0 = 0x00010000; 
	GPKDAT  = 0;

	uart0_init();

	while(1)
	{
		unsigned char ch;
		uart0_putc(100);
		ch = uart0_getc();
	}

	return 0;
}

