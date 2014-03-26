/*
 * (C) 2014 JinDongHuang
 *
 * include/s3c6410.h
 *
 * registers for s3c6410    
 *
 */

/* GPIO */
#define GPACON      (*(volatile unsigned long *)0x7F008000)     
#define GPADAT      (*(volatile unsigned long *)0x7F008004)
#define GPAPUD      (*(volatile unsigned long *)0x7F008008)
#define GPKCON0     (*(volatile unsigned long *)0x7F008800)
#define GPKDAT      (*(volatile unsigned long *)0x7F008808)

/* UART */
#define ULCON0      (*(volatile unsigned long *)0x7F005000)
#define UCON0       (*(volatile unsigned long *)0x7F005004)
#define UFCON0      (*(volatile unsigned long *)0x7F005008)
#define UMCON0      (*(volatile unsigned long *)0x7F00500c)
#define UTRSTAT0    (*(volatile unsigned long *)0x7F005010)
#define UFSTAT0     (*(volatile unsigned long *)0x7F005018)
#define UTXH0       (*(volatile unsigned char *)0x7F005020)
#define URXH0       (*(volatile unsigned char *)0x7F005024)
#define UBRDIV0     (*(volatile unsigned long *)0x7F005028)
#define UDIVSLOT0   (*(volatile unsigned long *)0x7F00502C)

/* Watch Dog */
#define WTCON       (*(volatile unsigned long *)0x7E004000)

