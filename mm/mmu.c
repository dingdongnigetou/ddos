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
 * 4096 L1 page descriptor, 256 L2 
 * per page is 4K -> total is 4G
 *
 */
#define ENABLE_SEMGMENT 1

#ifdef ENABLE_SEMGMENT
/*
 * Only L1 table page (Segment)
 * [31:20] which segment 
 * [11:10] AP [8:5] Domain
 * [4] must be 1
 * [3] C [2] B [1:0] is 2
 *
 */
#define MMU_BASE              0x51000000
#define MMU_SVC_ACCESS        (0 << 10)  /* only svc accsess */
#define MMU_FULL_ACCESS       (3 << 10)  /* all can access */
#define MMU_DOMAIN            (0 << 5)   /* which domain */
#define MMU_SPECIAL           (1 << 4)   /* bit 4 must be 1 */
#define MMU_WT                (0x2 << 2) /* write through */
#define MMU_WB                (0x3 << 2) /* write back */
#define MMU_SEGMENT           (2)        /* segment descriptor */

#define MMU_SECDESC           (MMU_FULL_ACCESS | MMU_DOMAIN | \
	                       MMU_SPECIAL | MMU_WB | MMU_SEGMENT)

#define SEG_TABLE             ((volatile unsigned long *)MMU_BASE)

#else
/*
 * L1 and L2 page table
 *
 * dir entry descriptor (Coarse)
 * [31:10] coarse base address
 * [8:5] Domain, [4] must be 1
 * [1:0] is 1 
 *
 * page entry descriptor (Small)
 * [31:12] small page base address
 * [11:4] ap(3-0) per ap take 2 bits
 * [3] C  [2] B [1:0] is 2
 *
 */

/*
 * dir entry (16K)
 */
#define MMU_DIR               0x50600000
#define MMU_DOMAIN            (0 << 5)   /* domain 0 */
#define MMU_SPECIAL           (1 << 4)   /* must be 1 */
#define MMU_COARSE            (1)        /* coarse page table */

/*
 * page table entry
 */
#define MMU_PAGE              (MMU_DIR + (16 << 10))
#define MMU_PAGE_N(N)         (MMU_PAGE + (N << 10))
#define MMU_FULL_ACCESS       (0xFF << 4)/* all can access */
#define MMU_SVC_ACCESS        (0x00 << 4)/* only system can access */
#define MMU_WT                (0x2 << 2) /* write through */
#define MMU_WB                (0x3 << 2) /* write back */
#define MMU_SMALL             (2)        /* small page (second) */

/*
 * which page table 
 */
#define PAGE_0_BASE           (0)
#define PAGE_PER_BASE         (1)
#define PAGE_KERNEL_BASE      (PAGE_PER_BASE + 256)

/*
 * descriptor flags
 */
#define MMU_COADESC           (MMU_DOMAIN | MMU_SPECIAL | MMU_COARSE)

#define MMU_SMALLDESC         (MMU_FULL_ACCESS | MMU_WB | MMU_SMALL)

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

	for (i = 0; i < 256; i++)
		SEG_TABLE[0x000 + i] = (0x00000000 + (i << 20)) | MMU_SECDESC;

	/*
	 * 256M peripheral
	 */
	for (i = 0; i < 256; i++)
		SEG_TABLE[0x100 + i] = (0x70000000 + (i << 20)) | MMU_SECDESC;

	for (i = 0; i < 256; i++)
		SEG_TABLE[0xC00 + i] = (0x50000000 + (i << 20)) | MMU_SECDESC;
}

#else
/*
 * for L1 and L2 page table mapping
 */
static void memory_map_L2()
{
	int i, j;

	/*
	 * L1 page entry
	 */
	DIR_TABLE[0x000] = MMU_PAGE_N(PAGE_0_BASE) | MMU_COADESC;
	/* 256M peripheral */
	for (i = 0; i < 256; i++)
		DIR_TABLE[0x100 + i] = MMU_PAGE_N((PAGE_PER_BASE + i)) |
		       	MMU_COADESC;
	/* kernel */
	for (i = 0; i < 3; i++)
		DIR_TABLE[0xC00 + i] = MMU_PAGE_N(PAGE_KERNEL_BASE + i) | 
			MMU_COADESC;

	/*
	 * L2 page entry
	 */
	for (j = 0; j < 256; j++)
		PAGE_TABLE_N(PAGE_0_BASE)[0x00 + j] = (0x00000000 + 
				(j << 12)) | MMU_SMALLDESC;
	/* for peripheral */
	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++)
			PAGE_TABLE_N((PAGE_PER_BASE + i))[0x00 + j] = (0x70000000 + 
					(i << 20) + (j << 12)) | MMU_SMALLDESC;
	/* kernel */
	for (i = 0; i < 3; i++)
		for (j = 0; j < 256; j++)
			PAGE_TABLE_N(PAGE_KERNEL_BASE + i)[0x00 + j] = 
				(0x50000000 + (i << 20) + (j << 12)) | MMU_SMALLDESC;

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

