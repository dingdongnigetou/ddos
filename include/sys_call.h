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

fn_ptr sys_call_table[] = { sys_ledop, sys_test };

#endif /* _SYS_CALL_H */

