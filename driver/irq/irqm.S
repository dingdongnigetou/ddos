 @;                                (C) 2014 Jindong Huang
 @; driver/irq/irqm.c

#include <mm/mem.h>

/* which interrupt */
#define INT_EINT0   0  /* 0 - 3 */
#define INT_EINT1   1  /* 4 - 11 */
#define INT_TIMER2 25
#define INT_TIMER4 28

#define VIC0IRQSTATUS   0x11200000
#define VIC0INTENABLE   0x11200010
#define VIC0INTENCLEAR  0x11200014

/* 0 -> lowest priority */
#define PRIORITY_0   0  /* TIMER4 */
#define PRIORITY_1   1  /* EINT0 */
#define PRIORITY_2   2  /* TIMER2 */
#define PRIORITY_3   3  /* EINT1 */

#define BINARY_0   (1 << INT_TIMER4)
#define BINARY_1   (1 << INT_EINT0)
#define BINARY_2   (1 << INT_TIMER2)
#define BINARY_3   (1 << INT_EINT1)

/* mask <= self's priority */
#define MASK_3  (BINARY_3)
#define MASK_2  (MASK_3 + BINARY_2)
#define MASK_1  (MASK_2 + BINARY_1)
#define MASK_0  (MASK_1 + BINARY_0)

.global irq_handler_prioriry
irq_handler_prioriry:
	LDR   sp, =IRQ_STACK
	SUB   lr, lr, #4
	STMDB r13!, {lr}
	MRS   r14, spsr
	STMDB r13!, {r10, r11, r12, r14}
	LDR   r14, =VIC0IRQSTATUS
	LDR   r10, [r14]
	MOV   r11, pc
	TST   r10, #BINARY_0
	BLNE  disable_lower
	TST   r10, #BINARY_1
	BLNE  disable_lower
	TST   r10, #BINARY_2
	BLNE  disable_lower
	TST   r10, #BINARY_3
	BLNE  disable_lower

disable_lower:
	SUB  r11, r14, r11
	LDR  r12, =priority_table
	LDRB r11, [r12, r11, LSR #3] @; mem8[tb1 + (r11 >> 3)] 
	ADR  r10, priority_masks
	LDR  r10, [r10, r11, LSL #2] @: fetch priority masks
	LDR  r14, =VIC0INTENABLE
	LDR  r12, [r14]
	AND  r12, r12, r10
	LDR  r14, =VIC0INTENCLEAR
	STR  r12, [r14]  @; mask irq

////////////////////////////////////////////////////////
@; It's funny, without this, irq can't well work...
@; And I don't know why... :)
@; Maybe you can figure out...
	STMDB sp!, {r14}
	STMDB sp!, {r0-r9}
	mov   r0, #0
	BL    putc
	LDMIA sp!, {r0-r9}
	LDMIA sp!, {r14}
///////////////////////////////////////////////////////

	MRS  r14, cpsr
	BIC  r14, r14, #0x80 @; enable inner irq
	MSR  cpsr_c, r14

	LDR  pc, [pc, r11, LSL #2]
	NOP

	.word system_timer_service
	.word key_service
	.word user_timer_service
	.word key_service

priority_masks:
	.word MASK_0
	.word MASK_1
	.word MASK_2
	.word MASK_3

priority_table:
	.byte PRIORITY_0
	.byte PRIORITY_1
	.byte PRIORITY_2
	.byte PRIORITY_3

system_timer_service:
	STMDB r13!, {r0-r9}
	BL    do_system_timer_service
	LDMIA r13!, {r0-r10}
	MRS   r11, cpsr
	ORR   r11, r11, #0x80 @; disable inner irq 
	MSR   cpsr_c, r11
	LDR   r11, =VIC0INTENABLE
	STR   r12, [r11]      @; enable extra irq
	LDMIA r13!, {r11, r12, r14}
	MSR   spsr_cxsf, r14
	LDMIA r13!, {pc}^

key_service:
	STMDB r13!, {r0-r9}
	BL    do_key_service
	LDMIA r13!, {r0-r10}
	MRS   r11, cpsr
	ORR   r11, r11, #0x80 @; disable extra irq
	MSR   cpsr_c, r11
	LDR   r11, =VIC0INTENABLE
	STR   r12, [r11]      @; enable inner irq
	LDMIA r13!, {r11, r12, r14}
	MSR   spsr_cxsf, r14
	LDMIA r13!, {pc}^

user_timer_service:
	STMDB r13!, {r0-r9}
	BL    do_user_timer_service
	LDMIA r13!, {r0-r10}
	MRS   r11, cpsr
	ORR   r11, r11, #0x80 @; disable extra irq
	MSR   cpsr_c, r11
	LDR   r11, =VIC0INTENABLE
	STR   r12, [r11]      @; enable inner irq
	LDMIA r13!, {r11, r12, r14}
	MSR   spsr_cxsf, r14
	LDMIA r13!, {pc}^

