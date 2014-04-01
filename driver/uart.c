/*
 * (C) 2014 JinDongHuang
 *
 * driver/serial.c
 *
 * The device driver of UART on s3c6410.
 * use the FIFO.
 *
 */

#include "uart.h"
#include "s3c6410.h"

#define UART_CLK        PCLK
#define UART_BAUD_RATE  115200
/* DIV_VAL = (PCLK / (b/s * 16)) - 1 */
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

void uart0_init(void)
{
	GPACON  &= ~0xff;
	GPACON  |= 0x22;    /* enable RXD0 and TXD0 */

	ULCON0  = 0x03;     /* 8N1 -> 8 bits No check 1 Stop bit */
	UCON0   = 0x05;     /* interrupt request or polling */
	UFCON0  = 0x01;     /* enable FIFO */
	UMCON0  = 0x00;     /* forbid Medem */

	UBRDIV0 = UART_BRD; /* baud rate is 115200 */
}

void putc(unsigned char c)
{
	/* don't send c if send FIFO is full */
	while ( UFSTAT0 & (1 << 14) );
	UTXH0 = c;
}

unsigned char getc()
{
	/* don't receive c if receive FIFO is full */
	while( (UFSTAT0 & 0x7f) ==0 );
	return URXH0;
}

