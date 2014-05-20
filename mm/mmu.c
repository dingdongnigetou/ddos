/*
 * (C) 2014 Jindong Huang
 *
 * mm/mmu.c
 *
 * initialize the MMU
 * 
 */

#define REGISTER_USE_CACHE    0
#define MMU_BASE              0x50360000

#define MMU_FULL_ACCESS       (3 << 10)  /* access permission */
#define MMU_DOMAIN            (0 << 5)   /* which domain */
#define MMU_SPECIAL           (1 << 4)   /* bit 4 must be 1 */
#define MMU_CACHEABLE         (1 << 3)   /* enable cache */
#define MMU_BUFFERABLE        (1 << 2)   /* enable write buffer */
#define MMU_SECDESC           (2)        /* segment descriptor */

#define MMU_SECDESC_WB        (MMU_FULL_ACCESS | MMU_DOMAIN | \
	                       MMU_SPECIAL | MMU_CACHEABLE |  \
	                       MMU_BUFFERABLE | MMU_SECDESC)

#define MMU_SECDESC_NCNB      (MMU_FULL_ACCESS | MMU_DOMAIN | \
	                       MMU_SPECIAL | MMU_SECDESC)

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
	"orr r1, r1, #3\n"            /* domain 0, Accesses are not checked */
	"mcr p15, 0, r1, c3, c0, 0\n" /* write domain 15:0 access permissions */
	"mrc p15, 0, r1, c1, c0, 0\n" /* Read control register */
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
	table[0x000] = 0 | MMU_SECDESC_WB;  

	/* 
	 * 256M peripheral
	 * va: 0x10000000~0x1FF00000 => 0x70000000 ~ 0x7FF00000
	 */
	for (i = 0; i < 256; i++)
		table[0x100 + i] = (0x70000000 + i) | MMU_SECDESC_WB;

	table[0xC00] = 0x50000000;
}

void mmu_init(void)
{
	volatile unsigned long *table = (volatile unsigned long *)MMU_BASE;
	
	memory_map(table);
	mmu_enable((unsigned long)table);
}

