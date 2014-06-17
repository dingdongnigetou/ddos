/*
 * (C) 2014 Jindong Huang
 *
 * include/timer.h
 *
 */

#ifndef _TIMER_H
#define _TIMER_H

#include <types.h>

void system_timer_tick(size_t ms);
void system_timer_stop();
void system_wait_timer_tick();

#endif /* _TIMER_H */

