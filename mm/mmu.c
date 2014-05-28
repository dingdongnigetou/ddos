/*
 * (C) 2014 Jindong Huang
 *
 * mm/mmu.c
 *
 * initialize the MMU
 *
 * 4096 first page descriptor, 256 second 
 * per page is 4K -> total is 4G
 *
 * so, first page table takes 16K room and the second
 * takes 1K, as the result, they take 16K * 1K == 16M
 *
 */

/*
 * First page descriptor (Coarse)
 *
 * [31:10] coarse base address
 * [8:5] Domain, [4] must be 1
 * [1:0] is 1 
 *
 * Second page descriptor (Small)
 *
 * [31:12] small page base address
 * [11:4] ap(3-0) per ap take 2 bits
 * [3] C  [2] B [1:0] is 2
 *
 */

/* after the frame buffer */
#define MMU_TABLE1            0x50600000
#define MMU_DOMAIN            (0 << 5)   /* domain 0 */
#define MMU_SPECIAL           (1)        /* must be 1 */
#define MMU_COARSE            (1)        /* coarse page table */

#define MMU_TABLE2            0x50604000
#define MMU_TABLE2_N(N)       (MMU_TABLE2 + (N << 10))
#define MMU_FULL_ACCESS       (0xFF << 4)/* access permission */
#define MMU_SVC_ACCESS        (0 << 10)  /* only system can access */
#define MMU_CACHEABLE         (1 << 3)   /* enable cache */
#define MMU_BUFFERABLE        (1 << 2)   /* enable write buffer */
#define MMU_SMALL             (2)        /* small page (second) */

#define MMU_COADESC           (MMU_DOMAIN | MMU_SPECIAL | MMU_COARSE)

#define MMU_SMALLDESC         (MMU_FULL_ACCESS | MMU_CACHEABLE | \
			       MMU_BUFFERABLE  | MMU_SMALL)

#define TABLE1                ((volatile unsigned long *)MMU_TABLE1)
#define TABLE2_N(N)           ((volatile unsigned long *)MMU_TABLE2_N(N))

/*
 *  To enable the MMU:
 *  1) Program the translation table base and domain access control registers.
 *  2) Program level 1 and level 2 page tables as required.
 *  3) Enable the MMU by setting bit 0 in the control register.
 *
 */
static void mmu_enable()
{
__asm__ (

	"mov r1, #0\n"
	"mcr p15, 0, r1, c7, c7, 0\n" /* disable ICaches and ÍDCaches */
	"mcr p15, 0, r1, c7, c10, 4\n"/* drain write buffer on v4 */
	"mcr p15, 0, r1, c8, c7, 0\n" /* disable TLB */

	"mcr p15, 0, %0, c2, c0, 0\n" /* write TTB register */
	"mrc p15, 0, r1, c3, c0, 0\n" /* read domain 15:0 access permissions */
	"orr r1, r1, #0\n"            /* disable accesses check */
	"mcr p15, 0, r1, c3, c0, 0\n" /* write domain 15:0 access permissions */

	"mrc p15, 0, r1, c1, c0, 0\n" /* Read control register */
	"orr r1, r1, #(1<<2)\n"       /* Dcache enable */
	"orr r1, r1, #(1<<12)\n"      /* Icache enable */
	"orr r1, r1, #(1<<14)\n"      /* Round robin replacement */
	"orr r1, r1, #(1<<0)\n"       /* MMU enable */
	"mcr p15,0,r1,c1, c0,0\n"     /* write control register */

	:
	: "r" (MMU_TABLE1)            /* c2 to restore the MMU table1 base */
	: "r1"
	);
}

static void memory_map()
{
	int i, j;

	/*
	 * First page descriptor
	 */
	TABLE1[0xC00] = MMU_TABLE2_N(0) | MMU_COADESC;
	TABLE1[0xC01] = MMU_TABLE2_N(1) | MMU_COADESC;
	TABLE1[0xC02] = MMU_TABLE2_N(2) | MMU_COADESC;
	/* 
	 * 256M peripheral
	 * va: 0x10000000~0x1FF00000 => 0x70000000 ~ 0x7FF00000
	 */
	for (i = 0; i < 256; i++)
		TABLE1[0x100 + i] = MMU_TABLE2_N((i + 3)) | MMU_COADESC;


	/*
	 * Second page descriptor
	 */
	for (i = 0; i < 3; i++)
		for (j = 0; j < 256; j++)
			TABLE2_N(i)[0x00 + j] = (0x50000000 + (i << 20) + 
					(j << 12)) | MMU_SMALLDESC;
	/*
	 * for peripheral
	 */
	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++)
			TABLE2_N((i + 3))[0x00 + j] = (0x70000000 + 
					(i << 20) + (j << 12)) | MMU_SMALLDESC;
}

void mmu_init(void)
{
	memory_map();
	mmu_enable();
}

