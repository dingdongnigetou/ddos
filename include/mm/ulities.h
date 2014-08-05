/*
 * (C) 2014 Jindong Huang
 *
 * include/mm/ulities.h
 */

#ifndef _ULITIES_H_
#define _ULITIES_H_

inline static void flush_tlb()
{
	unsigned int c8_format = 0;
	__asm__(MCR, p15, 0, c8_format, c8, c7, 0);
}

inline static void flush_cache()
{
	unsigned int c7_format = 0;
	__asm__(MCR, p15, 0, c7_format, c7, c7, 0);
}

inline static void flush_d_cache()
{
	unsigned int c7_format = 0;
	__asm__(MCR, p15, 0, c7_format, c7, c6, 0);
}

inline static void flush_i_cache()
{
	unsigned int c7_format = 0;
	__asm__(MCR, p15, 0, c7_format, c7, c5, 0);
}


#endif /* _ULITIES_H_ */

