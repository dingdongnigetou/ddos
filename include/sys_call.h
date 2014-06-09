/*
 * (C) 2014 Jindong Huang
 *
 * include/sys_call.h
 *
 */

#ifndef _SYS_CALL_H
#define _SYS_CALL_H

typedef int (*fn_ptr)();

extern int sys_ledop(int num, int op);
extern int sys_test();
extern int sys_enirq();
extern int sys_disirq();
extern int sys_enfiq();
extern int sys_disfiq();

fn_ptr sys_call_table[] = 
{ 
	sys_ledop, sys_test, sys_enirq, sys_disirq,
	sys_enfiq, sys_disfiq
};

#endif /* _SYS_CALL_H */

