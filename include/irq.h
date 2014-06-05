/*
 * (C) 2014 Jindong Huang
 *
 * include/irq.h
 *
 * Something about irq
 */

#ifndef _IRQ_H
#define _IRQ_H

#define ENABLE_IRQ                \
	__asm__(                      \
			"swi 0\n"             \
			"mrs r0, cpsr\n"      \
			"bic r0, r0, #0x80\n" \
			"msr cpsr, r0\n"      \
		   );

#define DISABLE_IRQ               \
	__asm__(                      \
			"mrs r0, cpsr\n"      \
			"orr r0, r0, #0x80\n" \
			"msr cpsr, r0\n"      \
		   );

#endif /* _IRQ_H */

