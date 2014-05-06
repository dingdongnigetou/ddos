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
 * The shell of uart_putc() and lcd_putc()
 * handle the '\r' and '\n'
 *
 */
void putc(unsigned char c);

/*
 * The shell of uart_getc()
 *
 */
unsigned char getc();

/*
 * Output the string on screen. 
 *
 * return the length of string.
 *
 */
int puts(const char *s);

/*
 * Input the string into buf.
 *
 * return the length of input string.
 *
 */
int gets(char *buf);

#endif /* _IO_H_ */

