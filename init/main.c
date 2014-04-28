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

	char buf[1024];

	puts("hello world\n");
	while(1)
	{

		gets(buf);
		puts(buf);
		ledone_flicker();
	}

	return 0;
}

