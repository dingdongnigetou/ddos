/*
 * (C) 2014 Jindong Huang
 *
 * driver/irq.c
 *
 */

#include <s3c6410.h>

#define ENABLE_TIMER4 (1 << 28)
#define ENABLE_KEYBD  (1 << 22)

static void irq_init(void)
{
	VIC0INTENABLE &= ~(0xFFFFFFFF);
	VIC0INTENABLE |= ENABLE_TIMER4;
	VIC0INTENABLE |= ENABLE_KEYBD;
}

int sys_enirq()
{
	irq_init();

	asm(                          
		"mrs r0, spsr\n"
		"bic r0, r0, #0x80\n" 
		"msr spsr, r0\n" 
	   );

	return 0;
}

int sys_disirq()
{
	asm(                     
		"mrs r0, spsr\n"
		"orr r0, r0, #0x80\n"
		"msr spsr, r0\n"
	   );

	return 0;
}

