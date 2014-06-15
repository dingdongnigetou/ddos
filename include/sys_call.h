/*
 * (C) 2014 Jindong Huang
 *
 * include/sys_call.h
 *
 */

#ifndef _SYS_CALL_H
#define _SYS_CALL_H

#include <types.h>

typedef int (*fn_ptr)();

extern int sys_ledop(int num, int op);
extern int sys_test();
extern int sys_enirq();
extern int sys_disirq();
extern int sys_enfiq();
extern int sys_disfiq();
extern int sys_user_timer_tick(size_t ms);
extern int sys_user_timer_stop();
extern int sys_user_wait_timer_tick();

fn_ptr sys_call_table[] = 
{ 
	sys_ledop, sys_test, sys_enirq, sys_disirq,
	sys_enfiq, sys_disfiq, sys_user_timer_tick,
	sys_user_timer_stop, sys_user_wait_timer_tick
};

#endif /* _SYS_CALL_H */

