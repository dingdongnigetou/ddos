/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */

#define GPKCON0  (*(volatile unsigned long *)0x7F008800)
#define GPKDAT   (*(volatile unsigned long *)0x7F008808)

int main(void)
{
	GPKCON0 = 0x00010000; 
	GPKDAT  = 0;

	return 0;
}

