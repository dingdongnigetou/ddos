/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd.c
 *
 * The implementation of lcd driver, include 
 * some operations.
 *
 */

#include <s3c6410.h>
#include <string.h>
#include <common.h>
#include <types.h>
#include <font_8x8.h>

#define  VSPW           9
#define  VBPD           1
#define  LINEVAL        479
#define  VFPD           1

#define  HSPW           40    
#define  HBPD           1
#define  HOZVAL         799
#define  HFPD           1

#define  LeftTopX       0
#define  LeftTopY       0

#define  RightBotX      HOZVAL
#define  RightBotY      LINEVAL
#define  FRAME_BUFFER   0x51000000

#define  FRAME_BUFFER_P ((u_char *)FRAME_BUFFER)
#define  XSIZE          (HOZVAL + 1)
#define  YSIZE          (LINEVAL + 1)

#define  FRONT          50    /* front color */
#define  BACKGROUND     255   /* background color */

/* global var to store current cursor position */
static int lcd_x = 2;
static int lcd_y = 13;

/*
 * LCD controller fetch 24bits data from here
 * but not frame_buffer. frame_buffer store the
 * index so that save memory.
 */
static void palette_init()
{
	WIN0_PALENTRY0 = 0x56000000;

	volatile u_long *p = (volatile u_long *)WIN0_PALENTRY0;
	
	WPALCON |= (1<<9); /* ARM access */

	WPALCON &= ~(0x7);
	WPALCON |= 1;      /* 24-bit ( 8:8:8 ) */

	p[0] = 0x000000;
	p[1] = 0x00ff00; 
	p[2] = 0xff0000;
	p[3] = 0x0000ff;
	p[4] = 0xffffff;

	WPALCON &= ~(1<<9); /* LCD controller access */
}

/*
 * put color into (x, y)
 *
 */
static void put_pixel(u_int x, u_int y, u_int color)
{
	u_char *addr = FRAME_BUFFER_P + (y * XSIZE + x);
	//*addr = color; /* 24 bits */
	*addr = (u_char) color; /* 8 bits */ 
}

void clean_screen()
{
	memset(FRAME_BUFFER_P, BACKGROUND, XSIZE * YSIZE);

	/* resume the globals' cursor */
	lcd_x = 2;
	lcd_y = 13;
}

void lcd_init()
{
	GPICON = 0xAAAAAAAA;  
	GPJCON = 0xAAAAAAAA;   		

	GPECON &= ~(0xf);
	GPECON |= (0x1);

	MIFPCON &= ~(1<<3);   /* Normal mode */

	SPCON   &= ~(0x3);
	SPCON   |= 0x1;       /* RGB I/F style */

	/* RGB I/F, RGB Parallel format,  */
	VIDCON0 &= ~((3<<26) | (3<<17) | (0xff<<6)); 

	/* vclk== HCLK / (CLKVAL+1) = 133/(0+1) = 133MHz */
	VIDCON0 |= ((0<<6) | (1<<4));  

	VIDCON1 &= ~(1<<7);
	VIDCON1 |= ((1<<6) | (1<<5));

	VIDTCON0 = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
	VIDTCON1 = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	WINCON0 &= ~(0xf << 2);

	/* 8 BPP (palletized), byte swap */
	WINCON0 |= (0x3<<2) | (1<<17); 

	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1) / 4;

	VIDW00ADD0B0 = FRAME_BUFFER;
	VIDW00ADD1B0 = ((HOZVAL + 1) * (LINEVAL + 1)) & 0xffffff;

	palette_init();
	clean_screen();

	GPEDAT  |= (1 << 0);  /* lcd on */
	VIDCON0 |= 0x3;       /* display on */
	WINCON0 |= 1;
}

/*
 * draw a line between (x1, y1) and (x2, y2)
 *
 */
static void draw_line(int x1, int y1, int x2, int y2, int color)
{
	int dx, dy, e;
	dx = x2 - x1; 
	dy = y2 - y1;

	if(dx >= 0){
		if(dy >= 0){
			if(dx >= dy){
				e = dy - dx / 2;
				while (x1 <= x2){
					put_pixel(x1, y1, color);
					if (e > 0){
						y1 += 1;
						e -= dx;
					}   
					x1 += 1;
					e  += dy;
				}
			}
			else{
				e = dx - dy / 2;
				while (y1 <= y2){
					put_pixel(x1, y1, color);
					if (e > 0){
						x1 += 1;
						e -= dy;
					}   
					y1 += 1;
					e  += dx; } } } else{
			dy = -dy;   /* dy=abs(dy) */

			if(dx >= dy){
				e = dy - dx / 2;
				while(x1 <= x2){
					put_pixel(x1, y1, color);
					if(e > 0){
						y1 -= 1;
						e  -= dx;   
					}
					x1--;
					e += dy;
				}
			}
			else{
				e = dx-dy/2;
				while (y1 >= y2){
					put_pixel(x1, y1, color);
					if (e > 0){
						x1++;
						e -= dy;
					}   
					y1--;
					e += dx;
				}
			}
		}   
	}
	/* dx<0 */
	else{
		dx = -dx;  /* dx=abs(dx) */
		if (dy >= 0){
			if (dx >= dy){
				e = dy - dx / 2;
				while (x1 >= x2){
					put_pixel(x1, y1, color);
					if (e > 0){
						y1++;
						e -= dx;
					}   
					x1--;
					e += dy;
				}
			}
			else{
				e = dx-dy/2;
				while (y1 <= y2){
					put_pixel(x1, y1, color);
					if (e > 0){
						x1--;
						e -= dy;
					}   
					y1++;
					e += dx;
				}
			}
		}
		else{
			dy = -dy;

			if (dx>= dy){
				e = dy-dx/2;
				while (x1 >= x2){
					put_pixel(x1, y1, color);
					if (e > 0){
						y1--;
						e -= dx;
					}   
					x1--;
					e += dy;
				}
			}
			else{
				e = dx-dy/2;
				while (y1 >= y2){
					put_pixel(x1, y1, color);
					if (e > 0){
						x1--;
						e -= dy;
					}   
					y1--;
					e += dx;
				}
			}
		}   
	} /* else */
}

/*
 * hide the cursor
 *
 */
static void hide_cursor()
{
	draw_line(lcd_x, lcd_y, lcd_x, lcd_y + 8, BACKGROUND);
	draw_line(lcd_x + 1, lcd_y, lcd_x + 1, lcd_y + 8, BACKGROUND);
	draw_line(lcd_x + 2, lcd_y, lcd_x + 2, lcd_y + 8, BACKGROUND);
}

/*
 * show the cursor
 *
 */
static void show_cursor()
{
	draw_line(lcd_x, lcd_y, lcd_x, lcd_y + 8, FRONT);
	draw_line(lcd_x + 1, lcd_y, lcd_x + 1, lcd_y + 8, FRONT);
	draw_line(lcd_x + 2, lcd_y, lcd_x + 2, lcd_y + 8, FRONT);
}

void lcd_putc(u_char c)
{
	int    i, j;
	int    old_lcd_x;  /* save the old lcd x position */
	u_char line_dots;
	u_char *char_dots = fontdata_8x8 + c * 8;	

	//cursor_timer_stop();
	hide_cursor();

	if (c == NEWLINE){
		lcd_y += 10;
		if (lcd_y >= YSIZE){
			lcd_y = YSIZE - 10;
			memmove(FRAME_BUFFER_P, FRAME_BUFFER_P + 10 * XSIZE, 
					(YSIZE - 10) * (XSIZE - 2));
			/* keep background */
			memset(FRAME_BUFFER_P + (YSIZE - 10) * (XSIZE - 2), 4, 
					10 * XSIZE);
		}
		goto exit;
	}
	else if (c == RETURN){
		lcd_x = 2;
		goto exit;
	}
	else if (c == BACKSPACE){
		if (lcd_x > 2)
			lcd_x -= 8; /* back one ch */

		/* hide the front ch */
		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++)
				put_pixel(lcd_x + j, lcd_y + i, BACKGROUND);

		goto exit;
	}

	/* print ch */
	for (i = 0; i < 8; i++)	{
		line_dots = char_dots[i];

		for (j = 0; j < 8; j++){
			if (line_dots & (0x80 >> j))
				put_pixel(lcd_x + j, lcd_y + i, FRONT); 
			else
				put_pixel(lcd_x + j, lcd_y + i, BACKGROUND);  
		}
	}

	lcd_x += 8;
	if (lcd_x >= XSIZE)
		lcd_x = 2;

	if (lcd_x == 2){
		lcd_y += 10;
		if (lcd_y >= YSIZE){
			lcd_y = YSIZE - 10;
			memmove(FRAME_BUFFER_P, FRAME_BUFFER_P + 10 * XSIZE, 
					(YSIZE - 10) * (XSIZE - 2));
			/* keep background */
			memset(FRAME_BUFFER_P + (YSIZE - 10) * (XSIZE - 2), 4, 
					10 * XSIZE);
		}
	}

exit:
//	cursor_timer_start();
	show_cursor();	
}

