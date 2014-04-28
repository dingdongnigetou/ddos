/*
 * (C) 2014 Jindong Huang
 *
 * lib/io.c
 *
 * The implementation of input and output
 * functions.
 *
 */

#include "ioformat.h"
#include "string.h"
#include "common.h"
#include "uart.h"

int printf(const char *fmt, ...)
{

}

int scanf(const char * fmt, ...)
{

}

int puts(const char *s)
{
	if (s == NULL)
		return -1; 

	int i;
	int len = strlen(s);
	for (i = 0; i < len; i++){
		if (s[i] == NEWLINE)
			putc(RETURN);
		putc(s[i]);
	}

	return len;
}

int gets(char *buf)
{
	if (buf == NULL)
		return -1;

	int len = 0;
	unsigned char c;
	while ((c = getc()) != RETURN){
		putc(c);
		buf[len++] = c;
	}
	buf[len++] = NEWLINE;
	buf[len++] = '\0'; /* string ending */
	putc(NEWLINE);
	putc(RETURN);

	return len;
}

