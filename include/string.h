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

unsigned int strnlen(const char * s, unsigned int count);

void *memmove(void *dest, const void *src, unsigned int size);

void *memset(void *dest, int data, unsigned int size);

void *memcpy(void *dest, const void *src, unsigned int size);

#endif /* _STRING_H_ */

