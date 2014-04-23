/*
 * (C) 2014 Jindong Huang
 *
 * include/string.h
 *
 * The interface of string operation.
 *
 */

#ifndef _STRING_H_
#define _STRING_H_

void *memmove(void *dest, const void *src, unsigned int size);

void *memset(void *dest, int data, unsigned int size);

#endif /* _STRING_H_ */

