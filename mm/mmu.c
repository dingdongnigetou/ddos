/*
 * (C) 2014 Jindong Huang
 * 
 * mm/mmu.c
 */

#include <mm/mmu.h>

#define DEFALUTPAGE FAULT

static void mmu_map_master_table_region(Region *region);
static int  mmu_map_coarse_table_region(Region *region);
static int  mmu_map_fine_table_region(Region *region);

static int mmu_init_pt(Pagetable *pt)
{
	int index;
	unsigned int pte, *pte_ptr;
	pte_ptr = (unsigned int *) pt->pt_addr; /* base addr of page table */
	pte = FAULT;

	switch (pt->type)
	{
		case COARSE:
			index = 256 / 32;
			break;
		case MASTER:
			index = 4096 / 32;
			break;
		case FINE:
			index = 1024 / 32;
			break;
		default:
			return -1;
	}


	__asm__ (	
		"mov r0, %[pte]\n" 
		"mov r1, %[pte]\n"
		"mov r2, %[pte]\n"
		"mov r3, %[pte]\n"
		:
		:[pte]"r"(pte)
		);

	for (; index != 0; index--){
		__asm__(
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       "STMIA %[pte_ptr], {r0-r3}\n"
		       :
		       :[pte_ptr]"r"(pte_ptr)
		       );
	}

	return 0;
}

static int mmu_map_region(Region *region)
{
	switch (region->pt->type)
	{
	case MASTER:
		mmu_map_master_table_region(region);
		break;
	case COARSE:
		mmu_map_coarse_table_region(region);
		break;
	case FINE:
		mmu_map_fine_table_region(region);
		break;
	default:
		return -1;
	}

	return 0;
}

static void mmu_map_master_table_region(Region *region)
{
	int i;
	unsigned int *pte_ptr, pte;

	pte_ptr = (unsigned int *)region->pt->pt_addr;
	pte_ptr = region->va_addr >> 20; /* first page */
	pte_ptr = region->num_pages - 1; /* last page */

	pte = region->phy_addr & 0xfff00000;
	pte |= (region->ap & 0x3) << 10;
	pte |= (region->pt->dom)  << 5;
	pte |= (region->cb & 0x3) << 2;
	pte |= 0x12;

	for (i = region->num_pages - 1; i >= 0; i--)
		*pte_ptr-- = pte + (i << 20); /* 1M */

}

static int mmu_map_coarse_table_region(Region *region)
{
	int i, j;
	unsigned int *pte_ptr, pte;
	unsigned int temp_ap = region->ap & 0x3;

	pte_ptr = (unsigned int *)region->pt->pt_addr;

	switch (region->page_size)
	{
	case LAEGEPAGE:
		pte_ptr += (region->va_addr & 0x000ff000) >> 12; /* first page */
		pte_ptr += (region->num_pages * 16) - 1; /* last page */

		pte = region->phy_addr & 0xffff0000;
		pte |= temp_ap << 10;
		pte |= temp_ap << 8;
		pte |= temp_ap << 6;
		pte |= temp_ap << 4;
		pte |= (region->cb & 0x3) << 2;
		pte |= 0x1; /* set as large page */

		for (i = region->num_pages - 1; i >= 0; i--)
			for (j = 15; j >= 0; j--)
				*pte_ptr-- = pte + (i << 16); /* 64K */
		break;

	case SMALLPAGE:
		pte_ptr += (region->va_addr & 0x000ff000) >> 12; /* first page */
		pte_ptr += (region->num_pages - 1); /* last page */

		pte = region->phy_addr & 0xfffff000;
		pte |= temp_ap << 10;
		pte |= temp_ap << 8;
		pte |= temp_ap << 6;
		pte |= temp_ap << 4;
		pte |= (region->cb & 0x3) << 2;
		pte |= 0x2; /* set as small page */

		for (i = region->num_pages - 1; i >= 0; i--)
			*pte_ptr-- = pte + (i << 12); /* 4K */
		break;

	default:
		return -1;
	}

	return 0;
}

static int mmu_map_fine_table_region(Region *region)
{
	int i, j;
	unsigned int *pte_ptr, pte;
	unsigned int temp_ap = region->ap & 0x3;

	pte_ptr = (unsigned int *)region->pt->pt_addr;

	switch (region->page_size)
	{
	case LARGEPAGE:
		pte_ptr += (region->va_addr & 0x000ffc00) >> 10;
		pte_ptr += (region->num_pages *64) - 1;

		pte = region->phy_addr & 0xffff0000;
		pte |= temp_ap << 10;
		pte |= temp_ap << 8;
		pte |= temp_ap << 6;
		pte |= temp_ap << 4;
		pte |= (region->cb & 0x3) << 2;
		pte |= 0x1;
			
		for (i = region->num_pages - 1; i >= 0; i--)
			for (j = 63; j >= 0; j--)
				*pte_ptr-- = pte + (i << 16);

		break;

	case SMALLPAGE:
		pte_ptr += (region->va_addr & 0x000ffc00) >> 10;
		pte_ptr += (region->num_pages * 4) - 1;

		pte = region->phy_addr & 0xfffff000;
		pte |= temp_ap << 10;
		pte |= temp_ap << 8;
		pte |= temp_ap << 6;
		pte |= temp_ap << 4;
		pte |= (region->cb & 0x3) << 2;
		pte |= 0x2;

		for (i = region->num_pages - 1; i >=0; i--)
			for (j = 3; j >= 0; j--)
				*pte_ptr-- = pte + (i << 12);

		break;

	case TINYPAGE:
		pte_ptr += (region->va_addr & 0x000ffc00) >> 10;
		pte_ptr += (region->num_pages - 1);

		pte = region->phy_addr & 0xfffffc00;
		pte |= temp_ap << 4;
		pte |= (region->cb & 0x3) << 2;
		pte |= 0x3;

		for (i = region->num_pages - 1; i >= 0; i--)
			*pte_ptr-- = pte + (i << 10);

		break;

	default:
		return -1;

	}

	return 0;
}

static int mmu_attch_pt(Pagetable *pt)
{
	unsigned int *ttb;
        unsigned int pte, offset;

	ttb = (unsigned int *)pt->master_addr;
	offset = (pt->va_addr) >> 20;

	switch (pt->type)
	{
	case MASTER:
		__asm__ (MCR p15, 0, ttb, c2, c0, 0);
		break;

	case COARSE:
		pte = (pt->pt_addr & 0xfffffc00);
		pte |= pt->dom << 5;
		pte |= 0x11;
		ttb[offset] = pte;
		break;

	case FINE:
		pte = (pt->pt_addr & 0xfffff000);
		pte |= pt->dom << 5;
		pte |= 0x13;
		ttb[offset] = pte;
		break;

	default:
		return -1;
	}

	return 0;
}

static void domain_access_set(unsigned int value, unsigned int mask)
{
	unsigned int c3format;

	__asm__ (MRC p15, 0, c3format, c3, c0, 0);
	c3format &= ~mask;
	c3format &= value;
	__asm__ (MCR p15, 0, c3format, c3, c0, 0);
}

#define DOM3CLT           0x00000040
#define CHANGEALLDOM      0xffffffff

#define ENABLEMMU         0x00000001
#define ENABLEDCACHE      0x00000004
#define ENABLEICACHE      0x00001000
#define CHANGEMMU         0x00000001
#define CHANGEDCACHE      0x00000004
#define CHANGEICACHE      0x00001000
#define ENABLEWB          0x00000008
#define CHANGEWB          0x00000008

void mmu_init()
{
	unsigned int enable, change;	

	mmu_init_pt(&master_pt);
	mmu_init_pt(&system_pt);
	mmu_init_pt(&task3_pt);
	mmu_init_pt(&task2_pt);
	mmu_init_pt(&task1_pt);

	mmu_map_region(&kernel_region);
	mmu_map_region(&shared_region);
	mmu_map_region(&pagetable_region);
	mmu_map_region(&dismem_region);
	mmu_map_region(&periph_region);

	mmu_map_region(&task3_region);
	mmu_map_region(&task2_region);
	mmu_map_region(&task1_region);

	mmu_attch_pt(&master_pt);
	mmu_attch_pt(&system_pt);
	mmu_attch_pt(&task1_pt);

	domain_access_set(DOM3CLT, CHANGEALLDOM);

}


