/*
 * (C) 2014 Jindong Huang
 *
 * include/mem.h
 *
 * details are in doc/memory_map
 */

#ifndef _MEM_H_
#define _MEM_H_

#define ENABLE_MAP
#ifdef ENABLE_MAP

/* kernel code */
#define KERNEL_BASE    0xC0000000
#define KERNEL_END     0xC0020000

/* 
 * page directory table, must be physical address 
 * so -0x70000000 to convert it. 
 */
#define DIRTABLE_BASE  (KERNEL_END - 0x70000000)
#define PTTABLE_BASE   (DIRTABLE_BASE + (16 << 10))
#define DIRTABLE_END   (DIRTABLE_BASE + 0x100000)

/* display memory */
#define DISPMEM_BASE   (DIRTABLE_END + 0x70000000)
#define DISPMEM_END    (DISPMEM_BASE + 0x200000)

/* shared memory */
#define SHAREMEM_BASE  (DISPMEM_END)
#define SHAREMEM_END   (KERNEL_BASE + 0x400000)

//////////////////////////////////////////////////////

#else /* disable map */

/* kernel code */
#define KERNEL_BASE    0x50000000
#define KERNEL_END     0x50020000

/* display memory */
#define DISPMEM_BASE   (KERNEL_END + 0x2000000)
#define DISPMEM_END    (DISPMEM_BASE+ 0x200000)

/* shared memory */
#define SHAREMEM_BASE  (DISPMEM_END)
#define SHAREMEM_END   (KERNEL_BASE + 0x400000)

#endif /* ENABLE_MAP */

/* stack */
#define  USR_STACK (KERNEL_END)
#define  UND_STACK (USR_STACK - 0x10000)
#define  SWI_STACK (UND_STACK - 0x400)
#define  PBT_STACK (SWI_STACK - 0x1000)
#define  DBT_STACK (PBT_STACK - 0x400)
#define  NUD_STACK (DBT_STACK - 0x400)
#define  IRQ_STACK (NUD_STACK - 0x400)
#define  FIQ_STACK (IRQ_STACK - 0x1000)

/* size of region (K) */
#define KERNELSIZE    128
#define PAGETABLESIZE 1024
#define DISMEMSIZE    2048
#define SHAREBUFSIZE  896

#define PERIPHSIZE    256 * 1024
#define ZEROSIZE      1024

#endif /* _MEM_H_ */

