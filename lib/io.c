/*
 * (C) 2014 Jindong Huang
 *
 * lib/io.c
 *
 * The implementation of input and output
 * functions.
 *
 */

#include <io_format.h>
#include <string.h>
#include <common.h>
#include <uart.h>
#include <lcd.h>
#include <io.h>

int printf(const char *fmt, ...)
{

}

int scanf(const char * fmt, ...)
{

}

void putc(u_char c)
{
	uart_putc(c);
//	lcd_putc(c);

	if (c == RETURN){
		uart_putc(NEWLINE);
//		lcd_putc(NEWLINE);
	}
	else if (c == NEWLINE){
		uart_putc(RETURN);
//		lcd_putc(RETURN);
	}
	else if (c == BACKSPACE){
		uart_putc(SPACE);
		uart_putc(BACKSPACE);
	}

}

u_char getc()
{
	return uart_getc();
}

int puts(const char *s)
{
	int len;

	for (len = 0; s[len] != '\0'; len++){
		if (s[len] == NEWLINE)
			putc(RETURN);
		putc(s[len]);
	}

	return (len + 1);
}

int gets(char *buf)
{
	int    len = 0;
	u_char c;

	while ((c = getc()) != RETURN){
		putc(c);

		/* don't put ch when miss backspace */
		if (c != BACKSPACE)
			buf[len++] = c;
		else{
			/* back one ch */
			if (--len < 0)
				len = 0;  
		}
	}
	buf[len++] = NEWLINE;
	buf[len++] = '\0'; /* string ending */
	putc(NEWLINE);
	putc(RETURN);

	return len;
}

