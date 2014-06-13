/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include <unistd.h>
#include <s3c6410.h>
#include <led.h>
#include <lcd.h>
#include <io.h>

void led1()
{
	GPKCON0 = 0x00010000;
	GPKDAT  = 0;
}

void led2()
{
	GPKCON0 = 0x00100000;
	GPKDAT  = 0;
}

int main()
{	
	enirq();
	enfiq();
	
	while(1){
		char c;
		c = getc();
		putc(c);

	}

	return 0;
}

