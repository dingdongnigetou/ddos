/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include "s3c6410.h"
#include "bg_light.h"
#include "nand.h"
#include "lcd.h"
#include "led.h"
#include "io.h"

int main()
{

	char ch;

	while(1)
	{
		ch = getc();
		putc(ch);

		ledone_flicker();
	}

	return 0;
}

