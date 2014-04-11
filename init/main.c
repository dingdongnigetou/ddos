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
	set_bglight(25);

	while(1)
	{
		unsigned char ch;
		ch = getc();
		putc(ch);
		ledone_flicker();
	}

	return 0;
}

