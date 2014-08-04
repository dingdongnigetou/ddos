/*
 * (C) 2014 Jindong Huang
 *
 * include/mm/mmu.h
 */

#ifndef _MMU_H_
#define _MMU_H_

typedef struct
{
	unsigned int va_addr;
	unsigned int pt_addr;
	unsigned int dir_addr;
	unsigned int type;
	unsigned int dom;
} Pagetable;

typedef struct
{
	unsigned int va_addr;
	unsigned int page_size;
	unsigned int num_pages;
	unsigned int ap;
	unsigned int cb;
	unsigned int phy_addr;
	Pagetable    *pt;
} Region;

/* L1 */
#define FAULT    0
#define COARSE   1
#define SEGMENT  2
#define FINE     3

/* L2 */
#define LAEGE    1
#define SMALL    2
#define TINY     3

#endif /* _MMU_H_ */

