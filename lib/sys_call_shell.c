/*
 * (C) 2014 Jindong Huang
 *
 * lib/sys_call_shell.c
 *
 * system call's shell
 */

#define _SYSTEMCALL_
#include <unistd.h>
#include <types.h>

/* add here */
_syscall1(int, user_timer_tick, size_t, ms);
_syscall0(int, user_timer_stop);
_syscall0(int, user_wait_timer_tick);

