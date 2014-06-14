/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd/pwm.c
 *
 */
#include <s3c6410.h>
#include <pwm.h>

#define TINT_CSTAT_INIMASK(n)      ((n & 0x1F))
#define TIMER3_PENDING_CLEAR       (1 << 8)
#define TIMER3_INTERRRUPT_ENABLE   (1 << 3)
#define SYS_TIMER_PRESCALER        2
#define SYS_TIMER_DIVIDER          1

#define SAMPLE_BPS                 9600
#define REQ_INFO                   0x60

void timer_init()
{
	TCNTB3 = PCLK / SYS_TIMER_PRESCALER / SYS_TIMER_DIVIDER / SAMPLE_BPS - 1; 
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER3_PENDING_CLEAR;
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER3_INTERRRUPT_ENABLE;
}

void timer_start()
{
	TCON &= ~(1 << 16);   /* stop timer3 */
	TCON |= (1 << 17);    /* update TCNTB3 */
	TCON &= ~(1 << 17);
	/* auto reload, start timer3 */
	TCON |= ((1 << 19) | (1 << 16));
}

void timer_stop()
{
	TCON &= ~(1 << 16);
}

void waitTimerTick()
{
	while ((TINT_CSTAT & (1 << 8)) == 0);
	TINT_CSTAT = TINT_CSTAT_INIMASK(TINT_CSTAT) | TIMER3_PENDING_CLEAR;
}

