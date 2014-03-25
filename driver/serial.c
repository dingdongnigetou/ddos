/*
 * (C) 2014 JinDongHuang
 *
 * driver/serial.c
 *
 * The device driver of UART on s3c6410.
 *
 */

#include "serial.h"
#include "s3c6410.h"

#define TXD0READY   (1<<2)
#define RXD0READY   (1)

#define PCLK            66000000 
#define UART_CLK        PCLK
#define UART_BAUD_RATE  115200
/* DIV_VAL = (PCLK / (b/s * 16)) - 1 */
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

void uart0_init(void)
{
    GPACON  |= 0x22;    /* enable RXD0 and TXD0 */
    GPAPUD   = 0x0a;    /* GPA0, GPA1, pull up */

    ULCON0  = 0x03;     /* 8N1 -> 8 bits No check 1 Stop bit */
    UCON0   = 0x05;     /* interrupt request or polling */
    UFCON0  = 0x00;     /* forbid FIFO */
    UMCON0  = 0x00;     /* forbid Medem */
    UBRDIV0 = UART_BRD;       /* baud rate is 115200 */
}

void uart0_putc(unsigned char c)
{
	/* don't send c until Transmit buffer is empty */
	while ( !(UTRSTAT0 & TXD0READY) );
	UTXH0 = c;
}

unsigned char uart0_getc()
{
	/* pick up the data if receive buffer is no empty */
	while( !(UTRSTAT0 & RXD0READY) );
	
	return URXH0;
}

