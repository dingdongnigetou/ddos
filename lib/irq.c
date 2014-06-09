/*
 * (C) 2014 Jindong Huang
 *
 * lib/irq.c
 */

#define _SYSTEMCALL_
#include <unistd.h>

_syscall0(int, enirq);
_syscall0(int, disirq);

