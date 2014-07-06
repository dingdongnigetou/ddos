/*
 * (C) 2014 Jindong Huang
 *
 * driver/irq.c
 *
 */

#include <s3c6410.h>

/* VIC0INTENABLE */
#define ENABLE_TIMER4 (1 << 28)
#define ENABLE_EINT   (3 << 0)

/* VIC0INTENCLEAR */
#define CLEAR_TIMER4  (1 << 28)
#define CLEAR_EINT    (3 << 0)

/* clear int pending status */
#define TIMER2_PENDING_CLEAR    (1 << 7)
#define TIMER4_PENDING_CLEAR    (1 << 9)
#define EINT_PENDING_CLEAR      (0x3F)

void irq_init(void)
{
	GPNCON &= ~(0xfff);
	GPNCON |= 0xaaa;

	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x777;

	/* enable eint0-6 : key 1-6 */
	EINT0MASK &= ~(0x3f);

	VIC0INTENABLE &= ~(0xFFFFFFFF);
	VIC0INTENABLE |= ENABLE_TIMER4;
	VIC0INTENABLE |= ENABLE_EINT;
}

int sys_enirq()
{
__asm__(                          
	"mrs r0, spsr\n"
	"bic r0, r0, #0x80\n" 
	"msr spsr, r0\n" 
   	);

	return 0;
}

int sys_disirq()
{
__asm__(                     
	"mrs r0, spsr\n"
	"orr r0, r0, #0x80\n"
	"msr spsr, r0\n"
   	);

	return 0;
}

void do_key_service()
{
	int i;
	for (i = 0; i < 6; i ++){
		if (EINT0PEND & (1<<i)){
			/* release */
			if (GPNDAT & (1<<i))
				;
			/* press */
			else
				;
		}
	}

	EINT0PEND = 0;
	EINT0PEND |= EINT_PENDING_CLEAR;  /* clear int */
	VIC0ADDRESS = 0;
}

/* for test */
void delay(int x)
{
	for (int y = 1000; y >= 0; y--)
		for (; x >= 0; x--);
}

/*
 * It will call the schedule() in couple ms
 * to preempt cpu.
 */
void do_system_timer_service()
{
	/* do schedule() */
	delay(100);

	TINT_CSTAT &= 0x1F;
	TINT_CSTAT |= TIMER4_PENDING_CLEAR;
	VIC0ADDRESS = 0;
}

void do_user_timer_service()
{
	/* do something */

	TINT_CSTAT &= 0x1F;
	TINT_CSTAT |= TIMER2_PENDING_CLEAR;
	VIC0ADDRESS = 0;
}

