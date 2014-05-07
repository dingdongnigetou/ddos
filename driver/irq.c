/*
 * (C) 2014 Jindong Huang
 *
 * driver/irq.c
 *
 * The initialization of interrupt.
 *
 */

#include <s3c6410.h>

void irq_init()
{
	GPNCON &= ~(0xfff);
	GPNCON |= 0xaaa;

	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x777;

	EINT0MASK &= ~(0x3f);

	VIC0INTENABLE |= (0x3); /* bit0: eint0~3, bit1: eint4~11 */ 
}

