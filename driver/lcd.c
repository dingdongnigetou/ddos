/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd.c
 *
 * The implementation of lcd driver. 
 *
 */

#include "s3c6410.h"
#include "pwm.h"

#define  VSPW       9
#define  VBPD       1
#define  LINEVAL    768
#define  VFPD       1

#define  HSPW       40    
#define  HBPD       1
#define  HOZVAL     1024
#define  HFPD       1

#define  LeftTopX   0
#define  LeftTopY   0

#define  RightBotX  1024
#define  RightBotY  768 
#define  FRAME_BUFFER   0x54000000

/*
 * LCD controller fetch 24bits data from here
 * but not frame_buffer. frame_buffer store the
 * index so that save memory.
 */
static void palette_init()
{
	volatile unsigned long *p = (volatile unsigned long *)WIN0_PALENTRY0;
	
	WPALCON |= (1<<9);

	WPALCON &= ~(0x7);
	WPALCON |= 1;    /* 24-bit ( 8:8:8 ) */

	p[0] = 0xffffff; /* black */
	p[1] = 0x00ff00; 
	p[2] = 0xff0000;
	p[3] = 0x0000ff;
	p[4] = 0xffffff;

	WPALCON &= ~(1<<9);
}

static void clean_screem()
{
	int x;
	int y;
	int cnt = 0;
	
	volatile unsigned char *p = (volatile unsigned char *)FRAME_BUFFER;
	for (x = 0; x <=HOZVAL * 4; x++)
		for (y = 0; y <= LINEVAL * 4; y++)
			p[cnt++] = 100; /* black */
}

void lcd_init()
{
	GPICON = 0xAAAAAAAA;  
	GPJCON = 0xAAAAAAA;   		


	GPECON &= ~(0xf);
	GPECON |= (0x1);

	MIFPCON &= ~(1<<3);   /* Normal mode */

	SPCON   &= ~(0x3);
	SPCON   |= 0x1;       /* RGB I/F style */

	VIDCON0 &= ~((3<<26) | (3<<17) | (0xff<<6)  | (3<<2));     /* RGB I/F, RGB Parallel format,  */
	VIDCON0 |= ((14<<6) | (1<<4) );  /* vclk== HCLK / (CLKVAL+1) = 133/15 = 9MHz */

	VIDCON1 &= ~(1<<7);
	VIDCON1 |= ((1<<6) | (1<<5));

	VIDTCON0 = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
	VIDTCON1 = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	WINCON0 &= ~(0xf << 2);
	WINCON0 |= (0xb << 2); /* 24bits -> from FRAME_BUFFER */
	//WINCON0 |= (0x3<<2) | (1<<17);   /* 8 BPP (palletized), byte swap */

	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1) / 4;

	VIDW00ADD0B0 = FRAME_BUFFER;
	VIDW00ADD1B0 = (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);

//	palette_init();
//	clean_screem();
	GPEDAT  |= (1 << 0);  /* lcd on */
	VIDCON0 |= 0x3;       /* display on */
	WINCON0 |= 1;

}

