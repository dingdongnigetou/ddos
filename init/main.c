/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include "s3c6410.h"

int main(void)
{
	GPKCON0 = 0x00010000; 
	GPKDAT  = 0;

	return 0;
}

