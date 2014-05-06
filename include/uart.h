/*
 * (C) 2014 JinDongHuang
 *
 * include/serial.h
 *
 * The interface of serial.C.
 *
 */
#ifndef _SERIAL_H_ 
#define _SERIAL_H_

#include <types.h>

/* 
 * put data into UTXH0 
 *
 */
void uart_putc(u_char c);

/* 
 * pick up data from URXH0 
 *
 */
u_char uart_getc();               

/*
 * get ch no wait.
 *
 * if successful then return 0;
 * else return -1;
 *
 */
int uart_getc_nowait(u_char *pch);

/*
 * put ch no wait.
 *
 * if successful then return 0;
 * else return -1;
 *
 */
int uart_putc_nowait(u_char c);

#endif /* _SERIAL_H_ */

