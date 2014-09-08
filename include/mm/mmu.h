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
#define LAEGE    4
#define SMALL    5
#define TINY     6

/* page size */
#define SEGMENT   1024 /* 1M */
#define LARGEPAGE 64   /* 64KB */
#define SMALLPAGE 4    /* 4KB */
#define TINYPAGE  1    /* 1KB */

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
//Pagetable master_pt;// = {0xC0000000, 0x50020000, 0x50020000, MASTER, 0};
//////Pagetable system_pt  = {};
//////Pagetable task1_pt   = {};
//////Pagetable task2_pt   = {};
//////Pagetable task3_pt   = {};
//////
///////* region */
//Region zero_region = { .phy_addr = 0x00000000};// = {0x00000000, 1024, 1, RWRW, WB, 0x00000000, &master_pt};
//
////zero_region.page_size = 1024;
////zero_region.num_pages = 1;
////zero_region.AP = RWRW;
////zero_region.CB = WB;
////zero_region.phy_addr = 0x00000000;
////zero_region.pt = &master_pt;
//
//Region kernel_region = { .phy_addr = 0x50000000};// {0xC0000000, 1024, 4, RWRW, WB, 0x50000000, &master_pt};
//////Region pagetable_region = {0x50400000, 1024, 2, RWRW, WB, 0x50400000, &master_pt};
//////Region dismem_region =    {0xC0220000, 1024, 256, RWRW, WB, 0x50220000, &master_pt};
//////Region shared_region =    {0xC0420000, 1024, 256, RWRW, WB, 0x50420000, &master_pt};
//Region periph_region = { .phy_addr = 0x70000000};//    {0x10000000, 1024, 256, RWRW, WB, 0x70000000, &master_pt};
//Region task1_region = {};
//Region task2_region = {};
//Region task3_region = {};


#endif /* _MMU_H_ */

