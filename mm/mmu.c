/*
 * (C) 2014 Jindong Huang
 *
 * mm/mmu.c
 *
 * initialize the MMU
 *
 * 256 segments, per segment is 1M
 *
 */

/*
 * [32:20] segment address, [11:10] AP
 * [8:5] Domain, [3] C, [2] B, [1:0]  
 *

/* after the frame buffer */
#define MMU_BASE              0x50600000

#define MMU_FULL_ACCESS       (3 << 10)  /* access permission */
#define MMU_SVC_ACCESS        (1 << 10)  /* only system can access */
#define MMU_DOMAIN            (0 << 5)   /* domain 0 */
#define MMU_SPECIAL           (1 << 4)   /* bit 4 must be 1 */
#define MMU_CACHEABLE         (1 << 3)   /* enable cache */
#define MMU_BUFFERABLE        (1 << 2)   /* enable write buffer */
#define MMU_SEGMENT           (2)        /* segment descriptor */
#define MMU_COARSE            (1)        /* coarse page table */
#define MMU_SMALL             (2)        /* small page (second) */

#define MMU_SECDESC_USER      (MMU_FULL_ACCESS | MMU_DOMAIN | \
	                           MMU_SPECIAL | MMU_CACHEABLE |  \
	                           MMU_BUFFERABLE | MMU_SECDESC)

#define MMU_SECDESC_SVC       (MMU_SVC_ACCESS | MMU_DOMAIN |  \
	                           MMU_SPECIAL | MMU_CACHEABLE |  \
	                           MMU_BUFFERABLE | MMU_SECDESC)

#define MMU_SECDESC_USER_NCNB (MMU_FULL_ACCESS | MMU_DOMAIN | \
	                            MMU_SPECIAL | MMU_SECDESC)

#define MMU_COADESC           (MMU_DOMAIN | MMU_SPECIAL | MMU_COARSE)

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
	: "r" (table)
	: "r1"
	);
}

static void memory_map(volatile unsigned long *table)
{
	int i;

	/* va: 0x00000000 => pa: 0 */
	table[0x000] = 0 | MMU_COADESC;  

	/* 
	 * 256M peripheral
	 * va: 0x10000000~0x1FF00000 => 0x70000000 ~ 0x7FF00000
	 */
	for (i = 0; i < 256; i++)
		table[0x100 + i] = (0x70000000 + (i << 20)) | MMU_COADESC;

	table[0xC00] = 0x50000000 | MMU_COADESC;
	table[0xC01] = 0x50100000 | MMU_COADESC;
	table[0xC02] = 0x50200000 | MMU_COADESC;
	table[0xC03] = 0x50300000 | MMU_COADESC;
	table[0xC04] = 0x50400000 | MMU_COADESC;
	table[0xC05] = 0x50500000 | MMU_COADESC;
	table[0xCF0] = 0x5F000000 | MMU_COADESC;

//	for (i = 0; i < 256; i++)
//		table[0x00 + i] = (0x00 + i) | MMU_SMALL_USER;
}

void mmu_init(void)
{
	volatile unsigned long *table = (volatile unsigned long *)MMU_BASE;
	
	memory_map(table);
	mmu_enable((unsigned long)table);
}

