/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd/lcdop.c
 *
 * The operation on lcd.
 */

#include "lcdop.h"
#include "string.h"

#define FONTDATAMAX    2048
#define FRAME_BUFFER_P ( (unsigned char *)0x54000000 )
#define XSIZE          (1024 + 1)
#define YSIZE          (768 + 1)

static int lcd_x = 0;
static int lcd_y = 0;

void hide_cursor();
void show_cursor();
void show_hide_cursor();

void put_pixel(unsigned int x, unsigned int y, unsigned int color)
{
	unsigned char *addr = FRAME_BUFFER_P + (y * XSIZE + x);
	*addr = color; /* 24 bits */
	// *addr = (unsigned char) color; /* 8 bits */ 
}

void draw_line(int x1, int y1, int x2, int y2, int color)
{
	int dx, dy, e;
	dx = x2-x1; 
	dy = y2-y1;

	if(dx >= 0){
		if(dy >= 0){
			if(dx >= dy){
				e = dy-dx/2;
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
				e = dx-dy/2;
				while (y1 <= y2){
					put_pixel(x1, y1, color);
					if (e > 0){
						x1 += 1;
						e -= dy;
					}   
					y1 += 1;
					e  += dx;
				}
			}
		}
		else{
			dy = -dy;   /* dy=abs(dy) */

			if(dx >= dy){
				e = dy-dx/2;
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
				e = dy-dx/2;
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

/* from font8x8.c */
extern const unsigned char fontdata_8x8[FONTDATAMAX];

void lcd_putc(unsigned char c)
{
	int i, j;
	unsigned char line_dots;

	unsigned char *char_dots = fontdata_8x8 + c * 8;	

	//cursor_timer_stop();
	//hide_cursor();

	if (c == '\n')
	{
		lcd_y += 8;
		if (lcd_y >= 768)
		{
			lcd_y = 768 - 8;
			memmove(FRAME_BUFFER_P, FRAME_BUFFER_P + 8*1024, (768-8) * 1024);
			memset(FRAME_BUFFER_P + (768-8)*1024, 0, 8*1024);
		}
		//goto exit;
	}
	else if (c == '\r')
	{
		lcd_x = 0;
		//goto exit;
	}

	for (i = 0; i < 8; i++)	
	{
		line_dots = char_dots[i];

		for (j = 0; j < 8; j++)
		{
			if (line_dots & (0x80 >> j))
				put_pixel(lcd_x + j, lcd_y + i, 255); 
			//else
			//	put_pixel(lcd_x + j, lcd_y + i, 0);  
		}
	}

	lcd_x += 8;
	if (lcd_x >= 1024)
		lcd_x = 0;

	if (lcd_x == 0)
	{
		lcd_y += 8;
		if (lcd_y >= 768)
		{
			lcd_y = 768 - 8;
			memmove(FRAME_BUFFER_P, FRAME_BUFFER_P + 8*1024, (768-8) * 1024);
			memset(FRAME_BUFFER_P + (768-8)*1024, 0, 8*1024);
		}
	}

exit:
//	cursor_timer_start();
	show_cursor();	
}

void show_cross(int x, int y)
{
	draw_line(x-5, y, x+5, y, 4);
	draw_line(x, y-5, x, y+5, 4);
}

void hide_cross(int x, int y)
{
	draw_line(x-5, y, x+5, y, 0);
	draw_line(x, y-5, x, y+5, 0);
}

void hide_cursor()
{
	draw_line(lcd_x, lcd_y, lcd_x, lcd_y+8, 0);
	draw_line(lcd_x+1, lcd_y, lcd_x+1, lcd_y+8, 0);
}

void show_cursor()
{
	draw_line(lcd_x, lcd_y, lcd_x, lcd_y+8, 4);
	draw_line(lcd_x+1, lcd_y, lcd_x+1, lcd_y+8, 4);
}

