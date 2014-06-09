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
	ledop(LED1, ON);
	enirq();
	enfiq();

	while(1){

	}

	return 0;
}

