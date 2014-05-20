/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include <s3c6410.h>
#include <bg_light.h>
#include <nand.h>
#include <led.h>
#include <uart.h>
#include <io.h>

int main()
{
	char ch;

	while(1)
	{
		ch = uart_getc();
		uart_putc(ch);
	}

	return 0;
}

