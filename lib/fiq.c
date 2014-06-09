/*
 * (C) 2014 Jindong Huang
 *
 * lib/fiq.c
 */

#define _SYSTEMCALL_
#include <unistd.h>

_syscall0(int, enfiq);
_syscall0(int, disfiq);

