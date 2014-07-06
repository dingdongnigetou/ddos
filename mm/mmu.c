/*
 * (C) 2014 Jindong Huang
 *
 * mm/mmu.c
 *
 * initialize the MMU
 *
 * Only L1 table (Segment)
 * 4096 L1 page descriptor, per is 1M.
 *
 * L1 and L2 page table
 * [coarse]
 * 4096 L1 page descriptor, 256 L2 
 * per page is 4K -> total is 4G
 * [fine]
 * 4096 L1 page descriptor, 1024 l2
 * per page is 4K -> total is 4G
 *
 */

#include <mm/mem.h>

#ifdef ENABLE_SEMGMENT
/*
 * Only L1 table page (Segment)
 * [31:20] which segment 
 * [11:10] AP [8:5] Domain
 * [4] must be 1
 * [3] C [2] B [1:0] is 2
 *
 */
#define MMU_BASE              (DIRTABLE_BASE)
#define MMU_PRI_ACCESS        (1 << 10)  /* only privilege mode can accsess (R/W)*/
#define MMU_ALL_ACCESS        (3 << 10)  /* all modes can access */
#define MMU_DOMAIN            (0 << 5)   /* which domain */
#define MMU_SPECIAL           (1 << 4)   /* bit 4 must be 1 */
#define MMU_WT                (0x2 << 2) /* write through */
#define MMU_WB                (0x3 << 2) /* write back */
#define MMU_SEGMENT           (2)        /* segment descriptor */

#define MMU_SECDESC_PRI       (MMU_PRI_ACCESS | MMU_DOMAIN | \
	                       MMU_SPECIAL | MMU_WB | MMU_SEGMENT)
#define MMU_SECDESC_ALL       (MMU_ALL_ACCESS | MMU_DOMAIN | \
	                       MMU_SPECIAL | MMU_WB | MMU_SEGMENT)

#define SEG_TABLE             ((volatile unsigned long *)MMU_BASE)

#else
/*
 * L1 and L2 page table
 *
 */

/*
 * dir entry
 */
#define MMU_DIR               (DIRTABLE_BASE)
#define MMU_DOMAIN            (0 << 5)   /* domain 0 */
#define MMU_SPECIAL           (1 << 4)   /* must be 1 */
#define MMU_COARSE            (1)        /* coarse page table */
#define MMU_FINE              (3)        /* fine page table */

/*
 * page table entry
 */
#define MMU_PAGE              (MMU_DIR + (16 << 10))
#define MMU_PAGE_N(N)         (MMU_PAGE + (N << 10))
#define MMU_ALL_ACCESS        (0xFF << 4)/* all modes can access */
#define MMU_PRI_ACCESS        (0x55 << 4)/* only privilege mode can access (R/W) */
#define MMU_WT                (0x2 << 2) /* write through */
#define MMU_WB                (0x3 << 2) /* write back */
#define MMU_SMALL             (2)        /* small page (second) 4K */
#define MMU_TINY              (3)        /* tiny page (second) 1K */

/*
 * which page table 
 */
#define PAGE_0_BASE           (0)
#define PAGE_PER_BASE         (PAGE_0_BASE + 1)
#define PAGE_OS_BASE          (PAGE_PER_BASE + 256)

/*
 * descriptor flags
 */
#define MMU_COADESC           (MMU_DOMAIN | MMU_SPECIAL | MMU_COARSE)
#define MMU_FINDESC           (MMU_DOMAIN | MMU_SPECIAL | MMU_FINE)
#define MMU_SMALLDESC_PRI     (MMU_PRI_ACCESS | MMU_WB | MMU_SMALL)
#define MMU_SMALLDESC_ALL     (MMU_ALL_ACCESS | MMU_WB | MMU_SMALL)
#define MMU_TINYDESC_PRI      (MMU_PRI_ACCESS | MMU_WB | MMU_TINY)
#define MMU_TINYDESC_ALL      (MMU_ALL_ACCESS | MMU_WB | MMU_TINY)

#define DIR_TABLE             ((volatile unsigned long *)MMU_DIR)
#define PAGE_TABLE_N(N)       ((volatile unsigned long *)MMU_PAGE_N(N))

#endif /* ENABLE_SEMGMENT */

#ifdef ENABLE_SEMGMENT
/*
 * for segment mapping
 */
static void memory_map_seg()
{
	int i;

	/* 
	 * va 0x00000000 - 0x000FFFFF
	 * pa 0x00000000 - 0x000FFFFF
	 */
	SEG_TABLE[0x000 + i] = (0x00000000 + (i << 20)) | 
		MMU_SECDESC_ALL;

	/*
	 * 256M peripheral
	 * va 0x10000000 - 0x1FFFFFFF
	 * pa 0x70000000 - 0x7FFFFFFF
	 */
	for (i = 0; i < 256; i++)
		SEG_TABLE[0x100 + i] = (0x70000000 + (i << 20)) | 
			MMU_SECDESC_ALL;

	/*
	 * 4M os code
	 */
	for (i = 0; i < 4; i++)
		SEG_TABLE[0xC00 + i] = (0x50000000 + (i << 20)) | 
			MMU_SECDESC_ALL;
}

#else
/*
 * for L1 and L2 page table mapping
 * see the details in doc/memory_map
 */
static void memory_map_L2()
{
	int i, j;

	/*
	 * va 0x00000000 - 0x000FFFFF
	 * pa 0x00000000 - 0x000FFFFF
	 */
	DIR_TABLE[0x000] = MMU_PAGE_N(PAGE_0_BASE) | 
			MMU_COADESC;
	for (j = 0; j < 256; j++)
		PAGE_TABLE_N(PAGE_0_BASE)[0x00 + j] = (0x00000000 + 
			(j << 12)) | MMU_SMALLDESC_ALL;

	/* 
	 * 256M peripheral 
	 * va 0x10000000 - 0x1FFFFFFF
	 * pa 0x70000000 - 0x7FFFFFFF
	 */
	for (i = 0; i < 256; i++)
		DIR_TABLE[0x100 + i] = MMU_PAGE_N((PAGE_PER_BASE + i)) |
		       	MMU_COADESC;
	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++)
			PAGE_TABLE_N((PAGE_PER_BASE + i))[0x00 + j] = 
				(0x70000000 + (i << 20) + (j << 12)) | 
				MMU_SMALLDESC_ALL;

	/*
	 * The os code total is 4M 
	 */
	for (i = 0; i < 4; i++)
		DIR_TABLE[0xC00 + i] = MMU_PAGE_N((PAGE_OS_BASE + i)) | 
			MMU_COADESC;
	/*
	 * kernel code
	 * pa: 0x50000000 - 0x50010000 (64K)
	 * set as privilege
	 */
	for (j = 0; j < 16; j++)
		PAGE_TABLE_N((PAGE_OS_BASE + 0))[0x00 + j] = 
			(0x50000000 + (0 << 20) + (j << 12)) | 
			MMU_SMALLDESC_PRI; 
	/*
	 * The rest of os code set as full permissions 
	 */
	for (j = 16; j < 256; j++)
		PAGE_TABLE_N((PAGE_OS_BASE + 0))[0x00 + j] = 
			(0x50000000 + (0 << 20) + (j << 12)) | 
			MMU_SMALLDESC_ALL; 
	for (i = 1; i < 4; i++)
		for (j = 0; j < 256; j++)
			PAGE_TABLE_N((PAGE_OS_BASE + i))[0x00 + j] = 
				(0x50000000 + (i << 20) + (j << 12)) | 
				MMU_SMALLDESC_ALL; 
}
#endif /* ENABLE_SEMGMENT */

/*
 *  To enable the MMU:
 *  1) Program the translation table base and domain access control registers.
 *  2) Program level 1 and level 2 page tables as required.
 *  3) Enable the MMU by setting bit 0 in the control register.
 *
 */
static void mmu_enable(unsigned long table)
{
__asm__ (
	"mov r1, #0\n"
	"mcr p15, 0, r1, c7, c7, 0\n" /* disable ICaches and ÍDCaches */
	"mcr p15, 0, r1, c7, c10, 4\n"/* drain write buffer on v4 */
	"mcr p15, 0, r1, c8, c7, 0\n" /* disable TLB */

	"mcr p15, 0, %0, c2, c0, 0\n" /* write TTB register */
	"mrc p15, 0, r1, c3, c0, 0\n" /* read domain 15:0 access permissions */
	"orr r1, r1, #1\n"            /* enable accesses check */
	"mcr p15, 0, r1, c3, c0, 0\n" /* write domain 15:0 access permissions */

	"mrc p15, 0, r1, c1, c0, 0\n" /* Read control register */
	"orr r1, r1, #(1<<2)\n"       /* Dcache enable */
	"orr r1, r1, #(1<<12)\n"      /* Icache enable */
	"orr r1, r1, #(1<<14)\n"      /* Round robin replacement */
	"orr r1, r1, #(1<<0)\n"       /* MMU enable */
	"mcr p15,0,r1,c1, c0,0\n"     /* write control register */

	:
	: "r" (table)                 /* c2 to restore the MMU dir table base */
	: "r1"
	);
}

void mmu_init(void)
{
#ifdef ENABLE_SEMGMENT
	memory_map_seg();
	mmu_enable((unsigned long)MMU_BASE);
#else
	memory_map_L2();
	mmu_enable((unsigned long)MMU_DIR);
#endif
}

