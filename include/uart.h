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

#endif /* _SERIAL_H_ */

