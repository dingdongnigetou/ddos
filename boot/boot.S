@;                 (C) 2014 Jindong Huang
@; boot/boot.S

#include <mm/mem.h>

nr_system_calls = 64

.global _start
_start:
	@; The table of exception vector
	B reset  @; 0x00
	LDR pc, __undefined_instruction @; 0x04 miss undefined instruction 
	LDR pc, __swi            @; 0x08 when run swi      
	LDR pc, __prefetch_abort @; 0x0C prefetch abort exception
	LDR pc, __data_abort     @; 0x10 data access exception
	LDR pc, __not_used       @; 0x14 not used 
	LDR pc, __irq            @; 0x18 interrupt exception 
	LDR pc, __fiq            @; 0x1C fast interrupt exception 

__undefined_instruction:
	.word undefined_instruction_handler
__swi:
	.word swi_handler
__prefetch_abort:
	.word prefetch_abort_handler
__data_abort:
	.word data_abort_handler
__not_used:
	.word not_used_handler
__irq:
	.word irq_handler_simple
__fiq:
	.word fiq_handler

bad_sys_call:
	MOV   r4, #-1
	LDMIA sp!, {r5-r12, pc}^ @;

undefined_instruction_handler:
	@; save spot
	LDR sp, =UND_STACK @; stack == 1k
	STMDB sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	LDMIA sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

swi_handler:
	LDR sp, =SWI_STACK @; stack == 4K
	@; save spot
	STMDB sp!, {r5-r12, lr}  @; lr is the instruction after swi

	CMP r3, #nr_system_calls-1
	BHI bad_sys_call @; > 63

@;	LDR r5, =sys_call_table
	LDR r6, [r5, r3, lsl #2] @; sys_call_table[num * 4]
	BLX r6	
	
	MOV r4, r0 @; return value

	@; resume
	LDMIA sp!, {r5-r12, pc}^ @; ^ is resume spsr to cpsr

prefetch_abort_handler:
	@; save spot	
	LDR sp, =PBT_STACK @; stack == 1K
	SUB lr, lr, #4
	STMDB sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	LDMIA sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

data_abort_handler:
	@; save spot	
	LDR sp, =DBT_STACK @; stack == 1K
	SUB lr, lr, #8
	STMDB sp!, {r0-r12, lr} @; corresponding system call


	@; handle exception

	@; resume
	LDMIA sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

not_used_handler:
	@; save spot	
	LDR sp, =NUD_STACK @; stack == 1K
	STMDB sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	LDMIA sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

irq_handler_simple:
	@; save spot	
	LDR sp, =IRQ_STACK @; stack == 4K
	SUB lr, lr, #4
	STMDB sp!, {r0-r12, lr}

#define VIC0IRQSTATUS   0x11200000
//#define VIC0IRQSTATUS   0x71200000
#define INT_EINT0       (1 << 0)
#define INT_EINT1       (1 << 1)
#define INT_TIMER2      (1 << 25)
#define INT_TIMER4      (1 << 28)

	LDR r0, =VIC0IRQSTATUS
	LDR r0, [r0]
	TST r0, #INT_TIMER4
@;	BLNE do_system_timer_service
	TST r0, #INT_EINT0
@;	BLNE do_key_service
	TST r0, #INT_TIMER2
@;	BLNE do_user_timer_service
	TST r0, #INT_EINT1
@;	BLNE do_key_service

	@; resume
	LDMIA sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

fiq_handler:
	@; save spot	
	LDR sp, =FIQ_STACK @; stack == 1K
	SUB lr, lr, #4
	STMDB sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	LDMIA sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

reset:
@; exchange to SVC mode 
	MRS r0, cpsr
	MOV r0, #0xd3
	MSR cpsr, r0 

@; peripheral setting
@; tell CPU peripheral where is  
@; 256M -> 0x70000000 - 0x7FFFFFFF
	LDR r0, =0x70000000 @; SROM_BW
	ORR r0,r0,#0x13
	MCR p15,0,r0,c15,c2,4

@; disable interrupt
	MOV r1, #0x0  
	LDR r0, =0x71200010
	STR r1, [r0]  
	LDR r0, =0x71300010 
	STR r1, [r0]

@; disable the watch dog
	LDR r0, =0x7E004000
	MOV r1, #0
	STR r1, [r0]

@; disable mmu
	MCR p15, 0, r0, c7, c7, 0    
	MRC p15, 0, r0, c1, c0, 0    
	BIC r0, r0, #0x00000007    
	MCR p15, 0, r0, c1, c0, 0  

@; set stack size == 8k
@; 8K is the MAX, but enough
	LDR sp, =1024 * 8 

@; initialization
	BL clock_init
	BL sdram_init
	BL mmu_init   @; after mapped
	BL nand_init

@; copy data form nand to ddr
@; by call copy2ddr
	ADR r0, _start  @; nand_start -> 0
	LDR r1, =_start

	LDR r2, =bss_start
	SUB r2, r2, r1

	CMP r0, r1
	BEQ clean_bss

	BL copy2ddr
	CMP r0, #0     @; error
	BNE halt

@; clean the bss
clean_bss:
	LDR r0, =bss_start
	LDR r1, =bss_end
	MOV r3, #0
	CMP r0, r1
	LDREQ pc, =on_ddr
clean_loop: 
	STR r3, [r0], #4
	CMP r0, r1
	BNE clean_loop
	LDR pc, =on_ddr

@;jump into DDR
on_ddr:
	@; exchange to sys mode 
	MRS r0, cpsr
	MOV r0, #0xdf
	MSR cpsr, r0 

	LDR sp, =USR_STACK

@;	BL uart_init 
@;	BL irq_init
@;	BL rtc_timer_init

	LDR pc, =main       @; pc == main link address  

halt:
	B halt

