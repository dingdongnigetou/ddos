/*
 * (C) 2014 Jindong Huang
 *
 * lib/io.c
 *
 * The implement of printf and scanf.
 * just the shell for vsprintf and vsscanf.
 *
 */

#include "vsprintf.h"
#include "uart.h"

#define	OUTBUFSIZE	1024
#define	INBUFSIZE	1024

static unsigned char g_pcOutBuf[OUTBUFSIZE];
static unsigned char g_pcInBuf[INBUFSIZE];

int printf(const char *fmt, ...)
{
	int i;
	int len;
	va_list args;

	va_start(args, fmt);
	len = vsprintf(g_pcOutBuf,fmt,args);
	va_end(args);
	for (i = 0; i < strlen(g_pcOutBuf); i++)
		putc(g_pcOutBuf[i]);

	return len;
}

int scanf(const char * fmt, ...)
{
	int      i = 0;
	unsigned char c;
	va_list  args;
	
	while(1){
		c = getc();

		if((c == '\r') || (c == '\n')){
			putc('\n');
			putc('\r');
			g_pcInBuf[i] = '\0';
			break;
		}
		else{
			g_pcInBuf[i++] = c;
			putc(c);
		}
	}
	
	va_start(args,fmt);
	i = vsscanf(g_pcInBuf,fmt,args);
	va_end(args);

	return i;
}

