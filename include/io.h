/*
 * (C) 2014 Jindong Huang
 *
 * include/io.h
 *
 * The interface of input and output
 * functions.
 *
 */

#ifndef _IO_H_
#define _IO_H_

/*
 * The shell of ddprintf()
 *
 */
int printf(const char *fmt, ...);

/*
 * The shell of ddscanf()
 *
 */
int scanf(const char *fmt, ...);

/*
 * Output the string on screen. 
 *
 * if successful
 *      return the length of string.
 * else
 *      return -1
 *
 */
int puts(const char *s);

/*
 * Input the string into buf.
 *
 * if successful
 *      return the length of input string.
 * else
 *      return -1
 *
 */
int gets(char *buf);

#endif /* _IO_H_ */

