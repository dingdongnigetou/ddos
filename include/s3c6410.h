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

#define ENABLE_MAP

/* clock */
#define APLL_LOCK          (*(volatile unsigned long *)0x7E00F000)
#define MPLL_LOCK          (*(volatile unsigned long *)0x7E00F004)
#define EPLL_LOCK          (*(volatile unsigned long *)0x7E00F008)
#define APLL_CON           (*(volatile unsigned long *)0x7E00F00C)
#define MPLL_CON           (*(volatile unsigned long *)0x7E00F010)
#define CLK_SRC            (*(volatile unsigned long *)0x7E00F01C)
#define CLK_DIV0           (*(volatile unsigned long *)0x7E00F020)
#define OTHERS             (*(volatile unsigned long *)0x7E00F900)

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

#ifdef  ENABLE_MAP

/* UART */
#define GPACON             (*(volatile unsigned long *)0x1F008000)     
#define GPADAT             (*(volatile unsigned long *)0x1F008004)
#define GPAPUD             (*(volatile unsigned long *)0x1F008008)
#define ULCON0             (*(volatile unsigned long *)0x1F005000)
#define UCON0              (*(volatile unsigned long *)0x1F005004)
#define UFCON0             (*(volatile unsigned long *)0x1F005008)
#define UMCON0             (*(volatile unsigned long *)0x1F00500c)
#define UFSTAT0            (*(volatile unsigned long *)0x1F005018)
#define UTXH0              (*(volatile unsigned char *)0x1F005020)
#define URXH0              (*(volatile unsigned char *)0x1F005024)
#define UBRDIV0            (*(volatile unsigned long *)0x1F005028)

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

/* Timer */
#define TCFG0              (*(volatile unsigned long *)0x1F006000)
#define TCFG1              (*(volatile unsigned long *)0x1F006004)
#define TCON               (*(volatile unsigned long *)0x1F006008)
#define TCNTB0             (*(volatile unsigned long *)0x1F00600C)
#define TCBTB1             (*(volatile unsigned long *)0x1F006018)
#define TCNTB2             (*(volatile unsigned long *)0x1F006024)
#define TCNTB3             (*(volatile unsigned long *)0x1F006030)
#define TCNTB4             (*(volatile unsigned long *)0x1F00603C)
#define TINT_CSTAT         (*(volatile unsigned long *)0x1F006044)

/* Nand Flash */
#define NFCONF             (*(volatile unsigned long *)0x10200000)
#define NFCONT             (*(volatile unsigned long *)0x10200004)
#define NFCMMD             (*(volatile unsigned long *)0x10200008)
#define NFADDR             (*(volatile unsigned long *)0x1020000C)
#define NFDATA             (*(volatile unsigned char *)0x10200010)
#define NFSTAT             (*(volatile unsigned long *)0x10200028)

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

#define VIC1IRQSTATUS      (*(volatile unsigned long *)0x11300000)
#define VIC1FIQSTATUS      (*(volatile unsigned long *)0x11300004)
#define VIC1RAWINTR        (*(volatile unsigned long *)0x11300008)
#define VIC1INTSELECT      (*(volatile unsigned long *)0x1130000c)
#define VIC1INTENABLE      (*(volatile unsigned long *)0x11300010)
#define VIC1INTENCLEAR     (*(volatile unsigned long *)0x11300014)
#define VIC1PROTECTION     (*(volatile unsigned long *)0x11300020)
#define VIC1SWPRIORITYMASK (*(volatile unsigned long *)0x11300024)
#define VIC1PRIORITYDAISY  (*(volatile unsigned long *)0x11300028)
#define VIC1ADDRESS        (*(volatile unsigned long *)0x11300f00)

/* rtc */
#define INTP               (*(volatile unsigned long *)0x1E005030) 
#define RTCCON             (*(volatile unsigned long *)0x1E005040) 
#define TICNT              (*(volatile unsigned long *)0x1E005044)
#define RTCALM             (*(volatile unsigned long *)0x1E005050)
#define ALMSEC             (*(volatile unsigned long *)0x1E005054)
#define ALMMIN             (*(volatile unsigned long *)0x1E005058)
#define ALMHOUR            (*(volatile unsigned long *)0x1E00505C)
#define ALMDATE            (*(volatile unsigned long *)0x1E005060)
#define ALMMON             (*(volatile unsigned long *)0x1E005064)
#define ALMYEAR            (*(volatile unsigned long *)0x1E005068)
#define BCDSEC             (*(volatile unsigned long *)0x1E005070)
#define BCDMIN             (*(volatile unsigned long *)0x1E005074)
#define BCDHOUR            (*(volatile unsigned long *)0x1E005078)
#define BCDDATE            (*(volatile unsigned long *)0x1E00507C)
#define BCDDAY             (*(volatile unsigned long *)0x1E005080)
#define BCDMON             (*(volatile unsigned long *)0x1E005084)
#define BCDYEAR            (*(volatile unsigned long *)0x1E005088)
#define CURTICNT           (*(volatile unsigned long *)0x1E005090)

/* Others */
#define PCLK   66500000 

#else /* disable map */

/* UART */
#define GPACON             (*(volatile unsigned long *)0x7F008000)     
#define GPADAT             (*(volatile unsigned long *)0x7F008004)
#define GPAPUD             (*(volatile unsigned long *)0x7F008008)
#define ULCON0             (*(volatile unsigned long *)0x7F005000)
#define UCON0              (*(volatile unsigned long *)0x7F005004)
#define UFCON0             (*(volatile unsigned long *)0x7F005008)
#define UMCON0             (*(volatile unsigned long *)0x7F00500c)
#define UFSTAT0            (*(volatile unsigned long *)0x7F005018)
#define UTXH0              (*(volatile unsigned char *)0x7F005020)
#define URXH0              (*(volatile unsigned char *)0x7F005024)
#define UBRDIV0            (*(volatile unsigned long *)0x7F005028)

/* GPIO */
#define GPFCON             (*(volatile unsigned long *)0x7F0080A0)
#define GPFDAT             (*(volatile unsigned long *)0x7F0080A4)
#define PRIORITY           (*(volatile unsigned long *)0x7F008280)
#define SERVICE            (*(volatile unsigned long *)0x7F008284)
#define SERVICEPEND        (*(volatile unsigned long *)0x7F008288)
#define GPNCON             (*(volatile unsigned long *)0x7F008830)
#define GPNDAT             (*(volatile unsigned long *)0x7F008834)
#define EINT0CON0          (*(volatile unsigned long *)0x7F008900)
#define EINT0MASK          (*(volatile unsigned long *)0x7F008920)
#define EINT0PEND          (*(volatile unsigned long *)0x7F008924)

/* Led */
#define GPKCON0            (*(volatile unsigned long *)0x7F008800)
#define GPKDAT             (*(volatile unsigned long *)0x7F008808)

/* LCD */
#define GPECON             (*(volatile unsigned long *)0x7F008080)
#define GPEDAT             (*(volatile unsigned long *)0x7F008084)
#define GPICON             (*(volatile unsigned long *)0x7F008100)
#define GPIDAT             (*(volatile unsigned long *)0x7F008104)
#define GPJCON             (*(volatile unsigned long *)0x7F008120)
#define SPCON              (*(volatile unsigned long *)0x7F0081A0)

#define MIFPCON            (*(volatile unsigned long *)0x7410800C)

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

/* Timer */
#define TCFG0              (*(volatile unsigned long *)0x7F006000)
#define TCFG1              (*(volatile unsigned long *)0x7F006004)
#define TCON               (*(volatile unsigned long *)0x7F006008)
#define TCNTB0             (*(volatile unsigned long *)0x7F00600C)
#define TCBTB1             (*(volatile unsigned long *)0x7F006018)
#define TCNTB2             (*(volatile unsigned long *)0x7F006024)
#define TCNTB3             (*(volatile unsigned long *)0x7F006030)
#define TCNTB4             (*(volatile unsigned long *)0x7F00603C)
#define TINT_CSTAT         (*(volatile unsigned long *)0x7F006044)

/* Nand Flash */
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

#define VIC1IRQSTATUS      (*(volatile unsigned long *)0x71300000)
#define VIC1FIQSTATUS      (*(volatile unsigned long *)0x71300004)
#define VIC1RAWINTR        (*(volatile unsigned long *)0x71300008)
#define VIC1INTSELECT      (*(volatile unsigned long *)0x7130000c)
#define VIC1INTENABLE      (*(volatile unsigned long *)0x71300010)
#define VIC1INTENCLEAR     (*(volatile unsigned long *)0x71300014)
#define VIC1PROTECTION     (*(volatile unsigned long *)0x71300020)
#define VIC1SWPRIORITYMASK (*(volatile unsigned long *)0x71300024)
#define VIC1PRIORITYDAISY  (*(volatile unsigned long *)0x71300028)
#define VIC1ADDRESS        (*(volatile unsigned long *)0x71300f00)

/* rtc */
#define INTP               (*(volatile unsigned long *)0x7E005030) 
#define RTCCON             (*(volatile unsigned long *)0x7E005040) 
#define TICNT              (*(volatile unsigned long *)0x7E005044)
#define RTCALM             (*(volatile unsigned long *)0x7E005050)
#define ALMSEC             (*(volatile unsigned long *)0x7E005054)
#define ALMMIN             (*(volatile unsigned long *)0x7E005058)
#define ALMHOUR            (*(volatile unsigned long *)0x7E00505C)
#define ALMDATE            (*(volatile unsigned long *)0x7E005060)
#define ALMMON             (*(volatile unsigned long *)0x7E005064)
#define ALMYEAR            (*(volatile unsigned long *)0x7E005068)
#define BCDSEC             (*(volatile unsigned long *)0x7E005070)
#define BCDMIN             (*(volatile unsigned long *)0x7E005074)
#define BCDHOUR            (*(volatile unsigned long *)0x7E005078)
#define BCDDATE            (*(volatile unsigned long *)0x7E00507C)
#define BCDDAT             (*(volatile unsigned long *)0x7E005080)
#define BCDMON             (*(volatile unsigned long *)0x7E005084)
#define BCDYEAR            (*(volatile unsigned long *)0x7E005088)
#define CURTICNT           (*(volatile unsigned long *)0x7E005090)

/* Others */
#define PCLK   66500000 

#endif  /* ENABLE_MAP */

#endif  /* _S3C6410_H_ */

