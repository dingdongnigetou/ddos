/*
 * (C) 2014 Jindong Huang
 * 
 * include/lcdop.h
 *
 * The interface of lcd operations.
 *
 */

#ifndef _LCDOP_H_
#define _LCDOP_H_

/*
 * put the pixel into (x, y) with color
 *
 */
void put_pixel(unsigned int x, unsigned int y, unsigned int color);

/*
 * draw a line between (x1, y1) and (x2, y2) with color
 *
 */
void draw_line(int x1, int y1, int x2, int y2, int color);

/*
 * clear the screen with color.
 *
 */
void clear_scr(unsigned int color);

#endif /* _LCDOP_H_ */

