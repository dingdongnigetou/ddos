/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include <unistd.h>
#include <led.h>

int main()
{	
	char c;
	asm("swi 0\n");

//	ledop(LED1, ON);
	while(1);

	return 0;
}

