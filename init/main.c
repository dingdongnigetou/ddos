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
#include "io.h"

int main()
{
	unsigned char ch;

	lcd_init();

	while(1)
	{
		printf("Hello World%d\n", 10);
		scanf("%c", &ch);
		putc(65);
		ledone_flicker();
	}

	return 0;
}

