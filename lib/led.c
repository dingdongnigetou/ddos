/*
 * (C) 2014 Jindong Huang
 *
 * lib/led.c
 */

#define  _SYSTEMCALL_
#include <unistd.h>

_syscall2(int, ledop, int, num, int, op)

