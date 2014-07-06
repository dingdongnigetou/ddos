/*
 * (C) 2014 Jindong Huang
 *
 * driver/irq/irqm.c
 *
 * mangement irq with priority
 */

/* which interrupt */
#define INT_EINT    (0x3)
#define INT_TIMER2  (1 << 25)
#define INT_TIMER4  (1 << 28)

#define VIC0IRQSTATUS   0x11200000
#define VIC0INTENABLE   0x11200010
#define VIC0INTENCLEAR  0x11200014

#define PRIORITY_0   28
#define PRIORITY_1   3
#define PRIORITY_2   25
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

.global irq_handler
irq_handler:
	SUB   r14, r14, #4
	STMFD r13!, {r14}
	MRS   r14, spsr
	STMFD r13!, {r10, r11, r12, r14}
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
	LDRB r11, [r12, r11, LSR #3] /* mem8[tb1 + (r11 >> 3)] */
	ADR  r10, priority_masks
	LDR  r10, [r10, r11, LSL #2] /* fetch priority masks */
	LDR  r14, =VIC0INTENABLE
	LDR  r12, [r14]
	AND  r12, r12, r10
	STR  r12, [r14]  /* enable extra irq */
	MRS  r14, cpsr
	BIC  r14, r14, #0x80 /* enable inner irq */
	MSR  cpsr_c, r14
	LDR  pc, [pc, r11, LSL #2]
	NOP

	.word system_timer_service
	.word key_service
	.word user_timer_service

priority_masks:
	.word MASK_2
	.word MASK_1
	.word MASK_0
	.word MASK_3

priority_table:
	.word PRIORITY_0
	.word PRIORITY_1
	.word PRIORITY_2
	.word PRIORITY_3

system_timer_service:
	STMFD r13!, {r0-r9}
	BL    do_system_timer_service
	LDMFD r13!, {r0-r10}
	MRS   r11, cpsr
	ORR   r11, r11, #0x80 /* disable irq */
	MSR   cpsr_c, r11
	LDR   r11, =VIC0INTENABLE
	STR   r12, [r11] /* enable irq */
	LDMFD r13!, {r11, r12, r14}
	MSR   spsr_cxsf, r14
	LDMFD r13!, {pc}^

key_service:
	STMFD r13!, {r0-r9}
	BL    do_key_service
	LDMFD r13!, {r0-r10}
	MRS   r11, cpsr
	ORR   r11, r11, #0x80 /* disable irq */
	MSR   cpsr_c, r11
	LDR   r11, =VIC0INTENABLE
	STR   r12, [r11] /* enable irq */
	LDMFD r13!, {r11, r12, r14}
	MSR   spsr_cxsf, r14
	LDMFD r13!, {pc}^

user_timer_service:
	STMFD r13!, {r0-r9}
	BL    do_user_timer_service
	LDMFD r13!, {r0-r10}
	MRS   r11, cpsr
	ORR   r11, r11, #0x80 /* disable irq */
	MSR   cpsr_c, r11
	LDR   r11, =VIC0INTENABLE
	STR   r12, [r11] /* enable irq */
	LDMFD r13!, {r11, r12, r14}
	MSR   spsr_cxsf, r14
	LDMFD r13!, {pc}^

