/*
 * (C) 2014 JinDongHuang
 *
 * include/s3c6410.h
 *
 * registers for s3c6410    
 *
 */

#ifndef _S3C6410_H_
#define _S3C6410_H_

/* GPIO */
#define GPACON             (*(volatile unsigned long *)0x7F008000)     
#define GPADAT             (*(volatile unsigned long *)0x7F008004)
#define GPAPUD             (*(volatile unsigned long *)0x7F008008)
#define GPECON             (*(volatile unsigned long *)0x7F008080)
#define GPEDAT             (*(volatile unsigned long *)0x7F008084)
#define GPFCON             (*(volatile unsigned long *)0x7F0080A0)
#define GPFDAT             (*(volatile unsigned long *)0x7F0080A4)
#define GPICON             (*(volatile unsigned long *)0x7F008100)
#define GPIDAT             (*(volatile unsigned long *)0x7F008104)
#define GPJCON             (*(volatile unsigned long *)0x7F008120)
#define GPJDAT             (*(volatile unsigned long *)0x7F008124)
#define SPCON              (*(volatile unsigned long *)0x7F0081A0)
#define PRIORITY           (*(volatile unsigned long *)0x7F008280)
#define SERVICE            (*(volatile unsigned long *)0x7F008284)
#define SERVICEPEND        (*(volatile unsigned long *)0x7F008288)
#define GPKCON0            (*(volatile unsigned long *)0x7F008800)
#define GPKDAT             (*(volatile unsigned long *)0x7F008808)
#define GPNCON             (*(volatile unsigned long *)0x7F008830)
#define GPNDAT             (*(volatile unsigned long *)0x7F008834)
#define EINT0CON0          (*(volatile unsigned long *)0x7F008900)
#define EINT0MASK          (*(volatile unsigned long *)0x7F008920)
#define EINT0PEND          (*(volatile unsigned long *)0x7F008924)


/* UART */
#define ULCON0             (*(volatile unsigned long *)0x7F005000)
#define UCON0              (*(volatile unsigned long *)0x7F005004)
#define UFCON0             (*(volatile unsigned long *)0x7F005008)
#define UMCON0             (*(volatile unsigned long *)0x7F00500c)
#define UTRSTAT0           (*(volatile unsigned long *)0x7F005010)
#define UFSTAT0            (*(volatile unsigned long *)0x7F005018)
#define UTXH0              (*(volatile unsigned char *)0x7F005020)
#define URXH0              (*(volatile unsigned char *)0x7F005024)
#define UBRDIV0            (*(volatile unsigned long *)0x7F005028)
#define UDIVSLOT0          (*(volatile unsigned long *)0x7F00502C)

/* Watch Dog */
#define WTCON              (*(volatile unsigned long *)0x7E004000)

/* clock */
#define APLL_LOCK          (*(volatile unsigned long *)0x7E00F000)
#define MPLL_LOCK          (*(volatile unsigned long *)0x7E00F004)
#define EPLL_LOCK          (*(volatile unsigned long *)0x7E00F008)
#define APLL_CON           (*(volatile unsigned long *)0x7E00F00C)
#define MPLL_CON           (*(volatile unsigned long *)0x7E00F010)
#define CLK_SRC            (*(volatile unsigned long *)0x7E00F01C)
#define CLK_DIV0           (*(volatile unsigned long *)0x7E00F020)
#define OTHERS             (*(volatile unsigned long *)0x7E00F900)

/* LCD */
#define VIDCON0            (*(volatile unsigned long *)0x77100000)
#define VIDCON1            (*(volatile unsigned long *)0x77100004)
#define VIDCON2            (*(volatile unsigned long *)0x77100008)
#define VIDTCON0           (*(volatile unsigned long *)0x77100010)
#define VIDTCON1           (*(volatile unsigned long *)0x77100014)
#define VIDTCON2           (*(volatile unsigned long *)0x77100018)
#define WINCON0            (*(volatile unsigned long *)0x77100020)
#define VIDOSD0A           (*(volatile unsigned long *)0x77100040)
#define VIDOSD0B           (*(volatile unsigned long *)0x77100044)
#define VIDOSD0C           (*(volatile unsigned long *)0x77100048)
#define VIDW00ADD0B0       (*(volatile unsigned long *)0x771000A0)
#define VIDW00ADD1B0       (*(volatile unsigned long *)0x771000D0)
#define VIDW00ADD2         (*(volatile unsigned long *)0x77100100)
#define WPALCON            (*(volatile unsigned long *)0x771001A0)
#define WIN0_PALENTRY0     (*(volatile unsigned long *)0x77100400)

/* Modem */
#define MIFPCON            (*(volatile unsigned long *)0x7410800C)

/* PWM */
#define TCFG0              (*(volatile unsigned long *)0x7F006008)
#define TCFG1              (*(volatile unsigned long *)0x7F006004)
#define TCON               (*(volatile unsigned long *)0x7F006008)
#define TCNTB0             (*(volatile unsigned long *)0x7F00600C)
#define TCMPB0             (*(volatile unsigned long *)0x7F006010)
#define TCNTB3             (*(volatile unsigned long *)0x7F006030)
#define TINT_CSTAT         (*(volatile unsigned long *)0x7F006044)

/* DRAM */
#define MEMCCMD	           (*(volatile unsigned long *)0x7E001004)
#define P1REFRESH          (*(volatile unsigned long *)0x7E001010)
#define P1CASLAT           (*(volatile unsigned long *)0x7E001014) 
#define MEM_SYS_CFG        (*(volatile unsigned long *)0x7E00F120)
#define P1MEMCFG           (*(volatile unsigned long *)0x7E00100C)
#define P1T_DQSS           (*(volatile unsigned long *)0x7E001018)
#define P1T_MRD	           (*(volatile unsigned long *)0x7E00101C)
#define P1T_RAS	           (*(volatile unsigned long *)0x7E001020)
#define P1T_RC	           (*(volatile unsigned long *)0x7E001024)
#define P1T_RCD	           (*(volatile unsigned long *)0x7E001028)
#define P1T_RFC	           (*(volatile unsigned long *)0x7E00102C)
#define P1T_RP	           (*(volatile unsigned long *)0x7E001030)
#define P1T_RRD	           (*(volatile unsigned long *)0x7E001034)
#define P1T_WR	           (*(volatile unsigned long *)0x7E001038)
#define P1T_WTR	           (*(volatile unsigned long *)0x7E00103C)
#define P1T_XP	           (*(volatile unsigned long *)0x7E001040)
#define P1T_XSR	           (*(volatile unsigned long *)0x7E001044)
#define P1T_ESR	           (*(volatile unsigned long *)0x7E001048)
#define P1MEMCFG2          (*(volatile unsigned long *)0X7E00104C)
#define P1_chip_0_cfg      (*(volatile unsigned long *)0x7E001200)

#define P1MEMSTAT          (*(volatile unsigned long *)0x7E001000)
#define P1MEMCCMD          (*(volatile unsigned long *)0x7E001004)
#define P1DIRECTCMD        (*(volatile unsigned long *)0x7E001008)

/* Nand Flash */
#define MEM_SYS_CFG        (*(volatile unsigned long *)0x7E00F120)
#define NFCONF             (*(volatile unsigned long *)0x70200000)
#define NFCONT             (*(volatile unsigned long *)0x70200004)
#define NFCMMD             (*(volatile unsigned long *)0x70200008)
#define NFADDR             (*(volatile unsigned long *)0x7020000C)
#define NFDATA             (*(volatile unsigned char *)0x70200010)
#define NFSTAT             (*(volatile unsigned long *)0x70200028)

/* Vector Interrupt */
#define VIC0IRQSTATUS      (*(volatile unsigned long *)0x71200000)
#define VIC0FIQSTATUS      (*(volatile unsigned long *)0x71200004)
#define VIC0RAWINTR        (*(volatile unsigned long *)0x71200008)
#define VIC0INTSELECT      (*(volatile unsigned long *)0x7120000c)
#define VIC0INTENABLE      (*(volatile unsigned long *)0x71200010)
#define VIC0INTENCLEAR     (*(volatile unsigned long *)0x71200014)
#define VIC0PROTECTION     (*(volatile unsigned long *)0x71200020)
#define VIC0SWPRIORITYMASK (*(volatile unsigned long *)0x71200024)
#define VIC0PRIORITYDAISY  (*(volatile unsigned long *)0x71200028)
#define VIC0ADDRESS        (*(volatile unsigned long *)0x71200f00)

/* Others */
#define PCLK   66500000 
#define TRUE   1
#define FLASE  0 

#endif /* _S3C6410_H_ */

