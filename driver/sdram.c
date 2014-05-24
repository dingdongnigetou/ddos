/*
 * (C) 2014 Jindong Huang
 *
 * driver/sdram.c
 *
 * initialize the ddr
 *
 */
#include <s3c6410.h>
#include <types.h>

#define set_zero( addr, bit ) ( addr &= ( ~ ( 1 << (bit) ) ) )
#define set_one( addr, bit )  ( addr |= ( 1 << ( bit ) ) )

#define set_2bit( addr, bit, val ) \
	( addr = (addr & (~(3<<(bit))) ) | ( (val)<<(bit) ) )

#define set_nbit( addr, bit, len,  val ) \
	( addr = ((addr & (~(( ((1<<(len))-1) )<<(bit))))  | ( (val)<<(bit) ) ))

#define HCLK	     133000000
#define nstoclk(ns)  (ns/( 1000000000/HCLK)+1)

void sdram_init()
{
	MEMCCMD   = 0x4;             /* tell dramc to configure */
	P1REFRESH = nstoclk(7800);   /* set refresh period */

	/* set timing para */
	P1CASLAT = 3 << 1;  
	P1T_DQSS = 0x1;    /* 0.75 - 1.25 */
	P1T_MRD  = 0x2;
	P1T_RAS  = nstoclk(45);
	P1T_RC   = nstoclk(68);		

	u_int trcd = nstoclk(23);
	P1T_RCD  = trcd | ( ( trcd - 3 ) << 3 );
	u_int trfc = nstoclk(80);
	P1T_RFC  = trfc | ( ( trfc-3 ) << 5 );   
	u_int trp = nstoclk(23);
	P1T_RP   = trp | ( ( trp - 3 ) << 3 ); 
	P1T_RRD  = nstoclk(15);
	P1T_WR   = nstoclk(15);
        P1T_WTR  = 0x7;
	P1T_XP   = 0x2;
	P1T_XSR  = nstoclk(120);
	P1T_ESR  = nstoclk(120);

	/* set mem cfg */
	set_nbit( P1MEMCFG, 0, 3, 0x2 );  /* 10 column address */
	set_nbit( P1MEMCFG, 3, 3, 0x2 );  /* 13 row address */
	set_zero( P1MEMCFG, 6 );	  /* A10/AP */
	set_nbit( P1MEMCFG, 15, 3, 0x2 ); /* Burst 4 */

	set_nbit( P1MEMCFG2, 0, 4, 0x5 );
	set_2bit( P1MEMCFG2, 6, 0x1 );	  /* 32 bit */
	set_nbit( P1MEMCFG2, 8, 3, 0x3 ); /* Mobile DDR SDRAM */
	set_2bit( P1MEMCFG2, 11, 0x1 );

	set_one( P1_chip_0_cfg, 16 );	  /* Bank-Row-Column organization */

	/* memory init */
	P1DIRECTCMD = 0xc0000;  /* NOP */
	P1DIRECTCMD = 0x000;	/* precharge */
	P1DIRECTCMD = 0x40000;  /* auto refresh */
	P1DIRECTCMD = 0x40000;  /* auto refresh */
	P1DIRECTCMD = 0xa0000;  /* EMRS */
	P1DIRECTCMD = 0x80032;  /* MRS */

	MEM_SYS_CFG = 0x0;

	/* set dramc to "go" status */
	P1MEMCCMD   = 0x000;

	/* wait ready */
	while( !((P1MEMSTAT & 0x3 ) == 0x1) );
}
