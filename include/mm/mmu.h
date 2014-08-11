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
	unsigned int master_addr;
	unsigned int type;
	unsigned int dom;
} Pagetable;

typedef struct
{
	unsigned int va_addr;
	unsigned int page_size;
	unsigned int num_pages;
	unsigned int AP;
	unsigned int CB;
	unsigned int phy_addr;
	Pagetable    *pt;
} Region;

/* L1 */
#define FAULT    0
#define COARSE   1
#define MASTER   2
#define FINE     3

/* L2 */
#define LAEGE    1
#define SMALL    2
#define TINY     3

/* page size */
#define LARGEPAGE (64 << 10) /* 64KB */
#define SMALLPAGE (4  << 10) /* 4KB */
#define TINYPAGE  (1  << 10) /* 1KB */

/* NA=not available RO=read only RW=read wirte */
#define NANA 0x00
#define RWNA 0x01
#define RWRO 0x02
#define RWRW 0x03

/*
 * cb = no cache and write buffer
 * cB = no cache but write buffer
 * WT = write throuh
 * WB = write back
 */
#define cb   0x0
#define cB   0x1
#define WT   0x2
#define WB   0x3

/* page table */
Pagetable master_pt = {0xC0000000, 0x50400000, 0x50400000, MASTER, 3};
//Pagetable system_pt  = {};
//Pagetable task1_pt   = {};
//Pagetable task2_pt   = {};
//Pagetable task3_pt   = {};
//
///* region */
Region kernel_region =    {0xC0000000, 1024, 4, RWRW, WT, 0x50000000, &master_pt};
Region pagetable_region = {0x50400000, 1024, 2, RWRW, WT, 0x50400000, &master_pt};
//Region dismem_region =    {0xC0220000, 1024, 256, RWRW, WT, 0x50220000, &master_pt};
//Region shared_region =    {0xC0420000, 1024, 256, RWRW, WT, 0x50420000, &master_pt};
Region periph_region =    {0x10000000, 1024, 256, RWRW, WT, 0x70000000, &master_pt};
//Region task1_region = {};
//Region task2_region = {};
//Region task3_region = {};

#endif /* _MMU_H_ */
