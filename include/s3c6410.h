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
#define GPFCON             (*(volatile unsigned long *)0x1F0080A0)
#define GPFDAT             (*(volatile unsigned long *)0x1F0080A4)
#define PRIORITY           (*(volatile unsigned long *)0x1F008280)
#define SERVICE            (*(volatile unsigned long *)0x1F008284)
#define SERVICEPEND        (*(volatile unsigned long *)0x1F008288)
#define GPNCON             (*(volatile unsigned long *)0x1F008830)
#define GPNDAT             (*(volatile unsigned long *)0x1F008834)
#define EINT0CON0          (*(volatile unsigned long *)0x1F008900)
#define EINT0MASK          (*(volatile unsigned long *)0x1F008920)
#define EINT0PEND          (*(volatile unsigned long *)0x1F008924)

/* Led */
#define GPKCON0            (*(volatile unsigned long *)0x1F008800)
#define GPKDAT             (*(volatile unsigned long *)0x1F008808)

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

/* UART */
#define GPACON             (*(volatile unsigned long *)0x7F008000)     
#define GPADAT             (*(volatile unsigned long *)0x7F008004)
#define GPAPUD             (*(volatile unsigned long *)0x7F008008)
#define ULCON0             (*(volatile unsigned long *)0x7F005000)
#define UCON0              (*(volatile unsigned long *)0x7F005004)
#define UFCON0             (*(volatile unsigned long *)0x7F005008)
#define UMCON0             (*(volatile unsigned long *)0x7F00500c)
#define UFSTAT0            (*(volatile unsigned long *)0x1F005018)
#define UTXH0              (*(volatile unsigned char *)0x1F005020)
#define URXH0              (*(volatile unsigned char *)0x1F005024)
#define UBRDIV0            (*(volatile unsigned long *)0x7F005028)

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
#define GPECON             (*(volatile unsigned long *)0x1F008080)
#define GPEDAT             (*(volatile unsigned long *)0x1F008084)
#define GPICON             (*(volatile unsigned long *)0x1F008100)
#define GPIDAT             (*(volatile unsigned long *)0x1F008104)
#define GPJCON             (*(volatile unsigned long *)0x1F008120)
#define SPCON              (*(volatile unsigned long *)0x1F0081A0)

#define MIFPCON            (*(volatile unsigned long *)0x1410800C)

#define VIDCON0            (*(volatile unsigned long *)0x17100000)
#define VIDCON1            (*(volatile unsigned long *)0x17100004)
#define VIDCON2            (*(volatile unsigned long *)0x17100008)
#define VIDTCON0           (*(volatile unsigned long *)0x17100010)
#define VIDTCON1           (*(volatile unsigned long *)0x17100014)
#define VIDTCON2           (*(volatile unsigned long *)0x17100018)
#define WINCON0            (*(volatile unsigned long *)0x17100020)
#define VIDOSD0A           (*(volatile unsigned long *)0x17100040)
#define VIDOSD0B           (*(volatile unsigned long *)0x17100044)
#define VIDOSD0C           (*(volatile unsigned long *)0x17100048)
#define VIDW00ADD0B0       (*(volatile unsigned long *)0x171000A0)
#define VIDW00ADD1B0       (*(volatile unsigned long *)0x171000D0)
#define VIDW00ADD2         (*(volatile unsigned long *)0x17100100)
#define WPALCON            (*(volatile unsigned long *)0x171001A0)
#define WIN0_PALENTRY0     (*(volatile unsigned long *)0x17100400)

/* PWM */
#define TCFG0              (*(volatile unsigned long *)0x1F006008)
#define TCFG1              (*(volatile unsigned long *)0x1F006004)
#define TCON               (*(volatile unsigned long *)0x1F006008)
#define TCNTB0             (*(volatile unsigned long *)0x1F00600C)
#define TCMPB0             (*(volatile unsigned long *)0x1F006010)
#define TCNTB3             (*(volatile unsigned long *)0x1F006030)
#define TINT_CSTAT         (*(volatile unsigned long *)0x1F006044)

/* Nand Flash */
#define MEM_SYS_CFG        (*(volatile unsigned long *)0x7E00F120)
#define NFCONF             (*(volatile unsigned long *)0x70200000)
#define NFCONT             (*(volatile unsigned long *)0x70200004)
#define NFCMMD             (*(volatile unsigned long *)0x70200008)
#define NFADDR             (*(volatile unsigned long *)0x7020000C)
#define NFDATA             (*(volatile unsigned char *)0x70200010)
#define NFSTAT             (*(volatile unsigned long *)0x70200028)

/* Vector Interrupt */
#define VIC0IRQSTATUS      (*(volatile unsigned long *)0x11200000)
#define VIC0FIQSTATUS      (*(volatile unsigned long *)0x11200004)
#define VIC0RAWINTR        (*(volatile unsigned long *)0x11200008)
#define VIC0INTSELECT      (*(volatile unsigned long *)0x1120000c)
#define VIC0INTENABLE      (*(volatile unsigned long *)0x11200010)
#define VIC0INTENCLEAR     (*(volatile unsigned long *)0x11200014)
#define VIC0PROTECTION     (*(volatile unsigned long *)0x11200020)
#define VIC0SWPRIORITYMASK (*(volatile unsigned long *)0x11200024)
#define VIC0PRIORITYDAISY  (*(volatile unsigned long *)0x11200028)
#define VIC0ADDRESS        (*(volatile unsigned long *)0x11200f00)

/* Others */
#define PCLK   66500000 

#endif /* _S3C6410_H_ */

