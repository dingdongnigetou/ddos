/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include "s3c6410.h"
#include "uart.h"
#include "led.h"
#include "bglight.h"

int main(void)
{
	uart0_init();
	set_bglight(10);

	unsigned char ch;

	while(1)
	{
		ch = getc();
		putc(ch);

		ledone_flicker();
	}

	return 0;
}

