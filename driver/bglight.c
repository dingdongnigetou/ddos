/*
 * (C) 2014 Jindong Huang
 *
 * driver/bglight.c
 *
 * The implement of set background light.
 *
 */

#include "bglight.h"
#include "s3c6410.h"

#define TIMER3_PENDING_CLEAR       (1 << 8)
#define TIMER3_INTERRRUPT_ENABLE   (1 << 3)

static void timer_init()
{
	TCNTB3 = 
	TINI_CSTAT |= TIMER3_PENDING_CLEAR;
	TINI_CSTAT |= TIMER3_INTERRRUPT_ENABLE;
}

static void timer_start()
{

}

static void timer_stop()
{

}

