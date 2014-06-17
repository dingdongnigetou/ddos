/*
 * (C) 2014 JinDongHuang
 *
 * driver/led.c
 *
 * The implement of led driver device.
 *
 */

#include <s3c6410.h>
#include <sys/sys_call.h>

/*
 * turn on or off the led num.
 */
int sys_ledop(int num, int op)
{
	if (num < 0 || num > 3 || op < 0 || op > 1)
		return -1;

	GPKCON0 = 0x00010000;
	GPKCON0 |= (1 << (16 + num * 4));	
	if (op == 1)
		GPKDAT = 0;
	else 
		GPKDAT = 0xffffffff;

	return 0;
}

int sys_test()
{
	return 0;
}

