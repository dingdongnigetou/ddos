/*
 * (C) 2014 Jindong Huang
 *
 * driver/timer.c
 *
 * use timer4 as system timer interrupt
 *
 */

#include <s3c6410.h>
#include <types.h>

#define TINT_CSTAT_INIMASK(n)   ((n & 0x1F))
#define TIMER4_PENDING_CLEAR    (1 << 9)
#define TIEMR4_INTERRUPT_ENABLE (1 << 4)

void system_timer_tick(size_t ms)
{
	/*
	 * fclk = PCLK / (prescaler + 1) / divider
	 */
	TCFG0 &= 0xFF00FF;
	TCFG0 |= 0xA500;   /* prescaler = 165 */
	TCFG1 &= ~0xF0000;
	TCFG1 |= 0x40000;  /* divider = 16, 25KHZ */

	TCNTB4 = ms * 25;
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | 
		         TIMER4_PENDING_CLEAR;
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) |
				 TIEMR4_INTERRUPT_ENABLE;

	TCON &= ~(1 << 20); /* stop timer4 */
	TCON |= (1 << 21);  /* update TCNTB4 */
	TCON &= ~(1 << 21);
	/* auto reload, start timer4 */
	TCON |= ((1 << 22) | (1 << 20));
}

void system_timer_stop()
{
	TCON &= ~(1 << 8);
}

void system_wait_timer_tick()
{
	while ((TINT_CSTAT & (1 << 9)) == 0);
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER4_PENDING_CLEAR;
}

