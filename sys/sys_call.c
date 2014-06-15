/*
 * (C) 2014 Jindong Huang
 *
 * sys/sys_call.c
 *
 * system call
 */

#include <s3c6410.h>
#include <types.h>

#define TINT_CSTAT_INIMASK(n)   ((n & 0x1F))
#define TIMER2_PENDING_CLEAR    (1 << 7)
#define TIEMR2_INTERRUPT_ENABLE (1 << 2)

/*
 * initialize timer2 
 */
int sys_user_timer_tick(size_t ms)
{
	TCFG0 &= 0xFF00FF;
	TCFG0 |= 0xA500;   /* prescaler = 165 */
	TCFG1 &= ~0xF00;
	TCFG1 |= 0x400;    /* divider = 16, 25KHZ */

	TCNTB2 = ms * 25;
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | 
		TIMER2_PENDING_CLEAR;
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) |
		TIEMR2_INTERRUPT_ENABLE;

	TCON &= ~(1 << 12); /* stop timer2 */
	TCON |= (1 << 13);  /* update TCNTB2 */
	TCON &= ~(1 << 13);
	/* auto reload, start timer2 */
	TCON |= ((1 << 15) | (1 << 12));

	return 0;
}

int sys_user_timer_stop()
{
	TCON &= ~(1 << 12);

	return 0;
}

int sys_user_wait_timer_tick()
{
	while ((TINT_CSTAT & (1 << 7)) == 0);
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER2_PENDING_CLEAR;

	return 0;
}

/* add here */

