/*
 * (C) 2014 Jindong Huang
 *
 * include/unistd.h
 *
 */

#ifndef _UNISTD_H
#define _UNISTD_H

#ifdef _SYSTEMCALL_

#define _NR_ledop 0
/* add _NR_##name here */

#define _syscall0(type, name)       \
type name()                         \
{                                   \
	long __res;                     \
	asm(                            \
			"swi 0\n"               \
			: "=r0"(__res)          \
			: "r"(_NR_##name)       \
			:                       \
		   );                       \
	if (__res >= 0)                 \
		return (type) __res;        \
	return -1;                      \
}                               

#define _syscall1(type, name, atype, a) \
type name(atype a)                  \
{                                   \
	long __res;                     \
	asm(                            \
			"swi 0\n"               \
			: "=r" (__res)          \
			  "r" (_NR_##name),     \
			  "r" ((long)(a))       \
		   );                       \
	if (__res >= 0)                 \
		return (type) __res;        \
	return -1;                      \
} 

#define _syscall2(type, name, atype, a, btype, b) \
type name(atype a, btype b)         \
{                                   \
	long __res;                     \
	asm(                            \
			"swi 0\n"               \
			: "=r"(__res)           \
			: "r"(_NR_##name),      \
			  "r"((long)(a)),       \
			  "r"((long)(b))        \
			:                       \
		   );                       \
	if (__res >= 0)                 \
		return (type) __res;        \
	return -1;                      \
} 

#define _syscall3(type, name, atype, a, btype, b, ctype, c) \
type name(atype a, btype b, ctype c)\
{                                   \
	long __res;                     \
	asm(                            \
			"swi 0\n"               \
			: "=r"(__res)           \
			: "r"(_NR_##name),      \
			  "r"((long)(a)),       \
			  "r"((long)(b)),       \
			  "r"((long)(c))        \
			:                       \
		   );                       \
	if (__res >= 0)                 \
		return (type) __res;        \
	return -1;                      \
} 

#endif /* _SYSTEMCALL_ */

int ledop(int num, int op);
/* add system call shell here */

#endif /* _UNISTD_H */
