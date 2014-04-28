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

/*
 * return the length of a length-limited string
 * 
 */
unsigned int strnlen(const char * s, unsigned int count);

/*
 * return the length of string
 *
 */
unsigned int strlen(const char *s);

/*
 * Copy data form src to dest. 
 * Unlike memcpy(), memmove can 
 * handle the overlapped area 
 *
 */
void *memmove(void *dest, const void *src, unsigned int size);

/*
 * Set continuous area's value as data.
 *
 */
void *memset(void *dest, int data, unsigned int size);

/*
 * Copy data from src to dest.
 *
 */
void *memcpy(void *dest, const void *src, unsigned int size);

#endif /* _STRING_H_ */

