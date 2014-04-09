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
#include "lcd.h"

int main(void)
{
	lcd_init();
	set_bglight(50);

	unsigned char ch;

	while(1)
	{
		ch = getc();
		putc(ch);
		ledone_flicker();
	}

	return 0;
}

