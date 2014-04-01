/*
 * (C) 2014 Jindong Huang
 *
 * driver/lcd.c
 *
 * The implementation of lcd driver. 
 *
 */

#include "lcd.h"
#include "s3c6410"

#define LCD_XSIZE 800
#define LCD_YSIZE 480

/* each pixel takes two bytes */
volatile static unsigned short LCD_BUFFER[LCD_YSIZE][LCD_XSIZE];

static void lcd_disable()
{

}

static void lcd_enable()
{

}

static void lcd_panel_disable()
{

}

void lcd_init()
{
	unsigned int pagewidth_in_byte = 0, offsize_in_byte = 0;
	unsigned int clkval = 0;
	unsigned int hsync_cnt, vclk_cnt;
	unsigned int lcd_horizon_value, lcd_line_value;
	unsigned int lcd_vbpd, lcd_vfpd, lcd_vspw, 
		     lcd_hbpd,lcd_hfp, lcd_hspw;

	lcd_horizon_value = LCD_XSIZE;
	lcd_line_value    = LCD_YSIZE;
	lcd_vbpd          = 

}

