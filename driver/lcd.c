/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd.c
 *
 * The implementation of lcd driver. 
 *
 */

#include "lcd.h"
#include "s3c6410.h"

#define  VSPW          9
#define  VBPD          1
#define  LINEVAL     271
#define  VFPD          1

#define  HSPW         40    
#define  HBPD          1
#define  HOZVAL      479
#define  HFPD          1

#define  LeftTopX      0
#define  LeftTopY      0

#define  RightBotX   479
#define  RightBotY   271

#define  FRAME_BUFFER   0x54000000

unsigned int fb_base_addr;
unsigned int bpp;
unsigned int xsize;
unsigned int ysize;

void palette_init(void)
{
	int i;
	volatile unsigned long *p = (volatile unsigned long *)WIN0_PALENTRY0;
	
	WPALCON |= (1<<9);

	WPALCON &= ~(0x7);
	WPALCON |= 1; /* 24-bit ( 8:8:8 ) */

	p[0] = 0x000000;
	p[1] = 0x00ff00;
	p[2] = 0xff0000;
	p[3] = 0x0000ff;
	p[4] = 0xffffff;

	for (i = 0; i <256; i++)
	{
		//p[i] = ;
	}
	
	WPALCON &= ~(1<<9);
}

void clean_screem(void)
{
	int x;
	int y;
	int cnt = 0;
	
	volatile unsigned char *p = (volatile unsigned char *)fb_base_addr;
	for (x = 0; x <=HOZVAL; x++)
		for (y = 0; y <= LINEVAL; y++)
			p[cnt++] = 0;
}

void lcd_init(void)
{
	GPICON = 0xaaaaaaaa;  
	GPJCON = 0xaaaaaaa;   		

	GPECON &= ~(0xf);
	GPECON |= (0x1);

	MIFPCON &= ~(1<<3);   /* Normal mode */

	SPCON    &= ~(0x3);
	SPCON    |= 0x1;      /* RGB I/F style */

	VIDCON0 &= ~((3<<26) | (3<<17) | (0xff<<6)  | (3<<2));     /* RGB I/F, RGB Parallel format,  */
	VIDCON0 |= ((14<<6) | (1<<4) );  /* vclk== HCLK / (CLKVAL+1) = 133/15 = 9MHz */

	VIDCON1 &= ~(1<<7);
	VIDCON1 |= ((1<<6) | (1<<5));

	VIDTCON0 = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
	VIDTCON1 = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	WINCON0 &= ~(0xf << 2);
	WINCON0 |= (0x3<<2) | (1<<17);    /* 8 BPP (palletized), byte swap */

	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1) / 4;

	VIDW00ADD0B0 = FRAME_BUFFER;
	VIDW00ADD1B0 =  (((HOZVAL + 1)*1 + 0) * (LINEVAL + 1)) & (0xffffff);

	palette_init();	
									
	fb_base_addr = FRAME_BUFFER;
	xsize = HOZVAL + 1;
	ysize = LINEVAL + 1;
	bpp   = 8;

	clean_screem();
}


void backlight_enable(void)
{
	//GPFDAT |= (1<<14);
}

void backlight_disable(void)
{
	//GPFDAT &= ~(1<<14);
}


void lcd_on(void)
{
	GPEDAT |= (1<<0);
}

void lcd_off(void)
{
	GPEDAT &= ~(1<<0);
}

void displaycon_on(void)
{
	VIDCON0 |= 0x3;
	WINCON0 |= 1;
}

void displaycon_off(void)
{
	VIDCON0 &= ~0x3;
	WINCON0 &= ~1;
}

void display_red(void)
{
	volatile unsigned char *p = (volatile unsigned char *)FRAME_BUFFER;
	int x, y;
	int cnt = 0;
	unsigned char colors[] = {0, 1, 2, 3};
	static int color_idx = 0;
	
	for (y = 0; y <= LINEVAL; y++)
	{
		for (x = 0; x <= HOZVAL; x++)
		{
			p[cnt++] =colors[color_idx] ;  /* red */
		}
	}

	color_idx++;
	if (color_idx == 5)
		color_idx = 0;
}

