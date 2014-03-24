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

void          uart0_init(void);      /* UART initialization */
void          uart0_putc(unsigned char c); /* put data into UTXH0 */
unsigned char uart0_getc();            /* pick up data from URXH0 */

#endif /* _SERIAL_H_ */

