/*
 * (C) 2014 Jindong Huang
 *
 * driver/nand.c
 *
 * The implement of nand flash driver.
 *
 */

#include "s3c6410.h"

#define TACLS     1  
#define TWRPH0    0
#define TWRPH1    0

static void nand_select()
{
	NFCONT &= ~(1<<1);
}

static void nand_deselect()
{
	NFCONT |= (1<<1); 
}

static void nand_cmd(unsigned char cmd)
{
	NFCMMD = cmd;
}

static void nand_addr(unsigned char addr)
{
	NFADDR = addr;
}

static unsigned char nand_get_data()
{
	return NFDATA;
}

static void nand_send_data(unsigned char data)
{
	NFDATA = data;
}

static void wait_ready()
{
	while ((NFSTAT & 0x1) == 0);
}

static void nand_reset()
{
	nand_select();
	nand_cmd(0xff);
	wait_ready();
	nand_deselect(); /* cancel selection */
}

void nand_init()
{
	/* xm0csn2 is the chip select pin of nand flash cs0 */
	MEM_SYS_CFG &= ~(1<<1);

	/* set time parameters */
	NFCONF &= ~((1<<30) | (7<<12) | (7<<8) | (7<<4));
	NFCONF |= ((TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4));

	/* enable nand flash controller */
	NFCONT |= 1;

	nand_reset();
}

static void nand_send_addr(unsigned int addr)
{
	/* col address */
	nand_addr(addr & 0xff);         /* a0~a7 */
	nand_addr((addr >> 8) & 0x7);   /* a8~a10 */

	/* row address */
	nand_addr((addr >> 11) & 0xff); /* a11~a18 */
	nand_addr((addr >> 19) & 0xff); /* a19~a26 */
	nand_addr((addr >> 27) & 0xff); /* a27 */
}

/* read data form nand flash to ddr */
static int nand_read(unsigned int nand_start, unsigned int ddr_start, 
		unsigned int len)
{
	unsigned int addr = nand_start;
	int i ;
	int count = 0;
	unsigned char *dest = (unsigned char *)ddr_start;
	
	nand_select();

	while (count < len)
	{
		nand_cmd(0x00);
		nand_send_addr(addr);
		nand_cmd(0x30);
		wait_ready();

		/* read data */
		for (i = 0; i < 2048 && count < len; i++)
			dest[count++] = nand_get_data();

		addr += 2048;
	}

	nand_deselect();
	return 0;
}

unsigned char test(int addr)
{

	unsigned char temp;
	nand_init();

	nand_select();
	nand_cmd(0x00);
	nand_send_addr(addr);
	nand_cmd(0x30);
	wait_ready();
	temp = nand_get_data();
	nand_deselect();

	return temp;
}

int nand_erase_block(unsigned long addr)
{
	int page = addr / 2048;
	
	nand_select();
	nand_cmd(0x60);
	
	nand_addr(page & 0xff);
	nand_addr((page >> 8) & 0xff);
	nand_addr((page >> 16) & 0xff);

	nand_cmd(0xd0);
	wait_ready();

	nand_deselect();
}

static void nand_write(unsigned int nand_start, unsigned char * buf, 
		unsigned int len)
{
	unsigned long count = 0;
	unsigned long addr  = nand_start;
	int i = nand_start % 2048; /* form which page */
	
	nand_select();

	while (count < len)
	{
		nand_cmd(0x80);
		nand_send_addr(addr);
		for (; i < 2048 && count < len; i++)
		{
			nand_send_data(buf[count++]);
			addr++;
		}

		nand_cmd(0x10);
		wait_ready();
		i = 0;		
	}

	nand_deselect();
}

/* called at boot.S */
int copy2ddr(unsigned int nand_start, unsigned int ddr_start, 
		unsigned int len)
{
	int ret;

	nand_init();
	ret =  nand_read(nand_start, ddr_start, len);

	return ret;
}

