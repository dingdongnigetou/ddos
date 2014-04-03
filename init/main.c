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
	uart0_init();
	set_bglight(50);
	lcd_init();
	display_red();

	unsigned char ch;

	while(1)
	{
		ch = getc();
		putc(ch);
		ledone_flicker();
	}

	return 0;
}

