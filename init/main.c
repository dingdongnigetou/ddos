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

int main()
{
	unsigned char ch;

	while(1)
	{
		ch = getc();
		putc(ch);
		set_bglight(ch);
		lcd_putc(ch);
	//	draw_line(0, 0, 1024, 768, ch);
		ledone_flicker();
	}

	return 0;
}

