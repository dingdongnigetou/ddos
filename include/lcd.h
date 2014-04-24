/*
 * (C) 2014 Jindong Huang
 * 
 * include/lcdop.h
 *
 * The interface of lcd.
 *
 */

#ifndef _LCDOP_H_
#define _LCDOP_H_


/*
 * initialize the lcd
 *
 */
void lcd_init();

/*
 * clear the screen with color.
 *
 */
void clean_screem(unsigned char color);

/*
 * put the c into lcd screen
 *
 */
void lcd_putc(unsigned char c);

#endif /* _LCDOP_H_ */

