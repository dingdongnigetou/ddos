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

#include <types.h>

/*
 * return the length of a length-limited string
 * 
 */
size_t strnlen(const char * s, size_t count);

/*
 * return the length of string
 *
 */
size_t strlen(const char *s);

/*
 * Copy data form src to dest. 
 * Unlike memcpy(), memmove can 
 * handle the overlapped area 
 *
 */
void *memmove(void *dest, const void *src, size_t size);
void *mem32move(void *dest, const void *src, size_t size);

/*
 * set the first size bytes of dest as 0.
 *
 */
void *bzero(void *dest, size_t size);

/*
 * Set continuous area's value as data.
 *
 */
void *memset(void *dest, int data, size_t size);
void *mem32set(void *dest, int data, size_t size);

/*
 * Copy data from src to dest.
 *
 */
void *memcpy(void *dest, const void *src, size_t size);

#endif /* _STRING_H_ */

