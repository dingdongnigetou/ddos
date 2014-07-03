/*
 * (C) 2014 Jindong Huang
 *
 * driver/irq/irqm.c
 *
 * mangement irq with priority
 */

#include <types.h>

/* which interrupt */
#define INT_EINT    0x00000003
#define INT_TIMER4  0x10000000

#define VIC0IRQSTATUS   0x11200000
#define VIC0INTENABLE   0x11200010
#define VIC0INTENCLEAR  0x11200014

#define PRIORITY_0   2
#define PRIORITY_1   1
#define PRIORITY_2   0
#define PRIORITY_3   3

#define BINARY_0   (1 << PRIORITY_0)
#define BINARY_1   (1 << PRIORITY_1)
#define BINARY_2   (1 << PRIORITY_2)
#define BINARY_3   (1 << PRIORITY_3)

/* mask <= self priority */
#define MASK_3  (BINARY_3)
#define MASK_2  (MASK_3 + BINARY_2)
#define MASK_1  (MASK_2 + BINARY_1)
#define MASK_0  (MASK_1 + BINARY_0)

u_int  priority_masks[] = {MASK_2, MASK_1, MASK_0, MASK_3};
u_char priority_table[] = {PRIORITY_0, PRIORITY_1, PRIORITY_2, PRIORITY_3};

void irq_handler()
{

}

void disable_lower()
{

}

