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

/* 
 * put data into UTXH0 
 *
 */
void uart_putc(unsigned char c);

/* 
 * pick up data from URXH0 
 *
 */
unsigned char uart_getc();               

#endif /* _SERIAL_H_ */

