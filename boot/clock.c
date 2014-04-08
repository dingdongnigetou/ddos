/*
 * (C) 2014 JinDongHuang
 *
 * boot/clock.c
 *
 * initialize clock
 *
 */

#include "s3c6410.h"

#define ARM_RATIO     0   /* ARMCLK = DOUTAPLL / (ARM_RATIO + 1) */
#define HCLKX2_RATIO  1   /* HCLKX2 = HCLKX2IN / (HCLKX2_RATIO + 1) */
#define HCLK_RATIO    1   /* HCLK = HCLKX2 / (HCLK_RATIO + 1) */
#define PCLK_RATIO    3   /* PCLK   = HCLKX2 / (PCLK_RATIO + 1) */
#define MPLL_RATIO    0   /* DOUTMPLL = MOUTMPLL / (MPLL_RATIO + 1 */

#define APLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (1))
#define MPLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (1))

void clock_init(void)
{
	APLL_LOCK = 0xffff;
	MPLL_LOCK = 0xffff;
	EPLL_LOCK = 0xffff;

	/* set async mode */
	OTHERS &= ~0xc0; 
	while ((OTHERS & 0xf00) != 0); 
	CLK_DIV0 = (ARM_RATIO) | (MPLL_RATIO << 4) | (HCLK_RATIO << 8) 
		    | (HCLKX2_RATIO << 9) | (PCLK_RATIO << 12);
	
	APLL_CON = APLL_CON_VAL;  /* 500MHz */
	MPLL_CON = MPLL_CON_VAL;  /* 500MHz */

	CLK_SRC = 0x03;

	return;
}

