/*
 * (C) 2014 Jindong Huang
 *
 * include/unistd.h
 *
 */

#ifndef _UNISTD_H
#define _UNISTD_H

#ifdef _SYSTEMCALL_

#define _NR_LENOP 0
/* add _NR_##name here */


#define _syscall0(type, name)           \
	type name()                         \
	{                                   \
		long __res;                     \
		__asm__(                        \
				"swi 0\n"               \
				: "=r0"(__res)          \
				: "0"(_NR_##name)       \
			   );                       \
		if (__res >= 0)                 \
			return (type) __res;        \
		return -1;                      \
	}                               

#define _syscall1(type, name, atype, a) \
	type name(atype a)                  \
	{                                   \
		long __res;                     \
		__asm__(                        \
				"swi 0\n"               \
				: "=r0"(__res)          \
				: "0"(_NR_##name)       \
				: "r1"((long)(a))       \
			   );                       \
		if (__res >= 0)                 \
			return (type) __res;        \
		return -1;                      \
	} 

#define _syscall2(type, name, atype, a, btype, b) \
	type name(atype a, btype b)         \
	{                                   \
		long __res;                     \
		__asm__(                        \
				"swi 0\n"               \
				: "=r0"(__res)          \
				: "0"(_NR_##name)       \
				: "r1"((long)(a))       \
				: "r2"((long)(b))       \
			   );                       \
		if (__res >= 0)                 \
			return (type) __res;        \
		return -1;                      \
	} 

#define _syscall2(type, name, atype, a, btype, b, ctype, c) \
	type name(atype a, btype b, ctype c)                    \
	{                                   \
		long __res;                     \
		__asm__(                        \
				"swi 0\n"               \
				: "=r0"(__res)          \
				: "0"(_NR_##name)       \
				: "r1"((long)(a))       \
				: "r2"((long)(b))       \
				: "r3"((long)(c))       \
			   );                       \
		if (__res >= 0)                 \
			return (type) __res;        \
		return -1;                      \
	} 

#endif /* _SYSTEMCALL_ */

int ledop(int num, int op);
/* add system call shell here */

#endif /* _UNISTD_H */

