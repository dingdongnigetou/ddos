/*
 * (C) 2014 Jindong Huang
 *
 * driver/nand.c
 *
 * The implement of nand flash driver.
 *
 */

#include <s3c6410.h>
#include <types.h>
#include <driver/nand.h>

#define TACLS     0
#define TWRPH0    2  /* shit me long time... */
#define TWRPH1    0

static void nand_select()
{
	NFCONT &= ~(1<<1);
}

static void nand_deselect()
{
	NFCONT |= (1<<1); 
}

static void nand_cmd(u_char cmd)
{
	NFCMMD = cmd;
}

static void nand_addr(u_char addr)
{
	NFADDR = addr;
}

static u_char nand_get_data()
{
	return NFDATA;
}

static void nand_send_data(u_char data)
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

static void nand_init()
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

static void nand_send_addr(u_int addr)
{
	/* col address 12bits -> 2K + 64Bytes */
	nand_addr(addr & 0xff);         /* a0~a7 */
	nand_addr((addr >> 8) & 0xff);  /* a8~a11 */

	/* row address 17bits -> 128K pages */
	nand_addr((addr >> 11) & 0xff); /* a12~a19 */
	nand_addr((addr >> 19) & 0xff); /* a20~a27 */
	nand_addr((addr >> 27) & 0xff); /* a28 */
}

/* read data form nand flash to ddr */
static int nand_read(u_int nand_start, u_int ddr_start, u_int len)
{
	u_int addr = nand_start;
	int i ;
	int count = 0;
	u_char *dest = (u_char *)ddr_start;
	
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

static void nand_erase_block(u_int addr)
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

void nand_erase_all()
{
	int i;

	for (i = 0; i < 128 * 1024; i++) 
		nand_erase_block(i);
}

void nand_write(u_int nand_start, u_char * buf, u_int len)
{
	nand_init();
	u_long count = 0;
	u_long addr  = nand_start;
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
int copy2ddr(u_int nand_start, u_int ddr_start, u_int len)
{
	int ret;

	nand_init();
	ret =  nand_read(nand_start, ddr_start, len);

	return ret;
}

