@;                 (C) 2014 Jindong Huang

nr_system_calls = 64

.global _start 
_start:
	@; The table of exception vector
	b reset  @; 0x00
	ldr pc, __undefined_instruction @; 0x04 miss undefined instruction 
	ldr pc, __swi            @; 0x08 when run swi      
	ldr pc, __prefetch_abort @; 0x0C prefetch abort exception
	ldr pc, __data_abort     @; 0x10 data access exception
	ldr pc, __not_used       @; 0x14 not used 
	ldr pc, __irq            @; 0x18 interrupt exception 
	ldr pc, __fiq            @; 0x1C fast interrupt exception 

__undefined_instruction:
	.word undefined_instruction
__swi:
	.word swi
__prefetch_abort:
	.word prefetch_abort
__data_abort:
	.word data_abort
__not_used:
	.word not_used
__irq:
	.word irq
__fiq:
	.word fiq

@; memory map value
#include <mem.h>
#define  UND_STACK (KERNEL_END)
#define  SWI_STACK (UND_STACK - 0x400)
#define  PBT_STACK (SWI_STACK - 0x800)
#define  DBT_STACK (PBT_STACK - 0x400)
#define  NUD_STACK (DBT_STACK - 0x400)
#define  IRQ_STACK (NUD_STACK - 0x400)
#define  FIQ_STACK (IRQ_STACK - 0x400)
#define  USR_STACK (FIQ_STACK - 0x400)


bad_sys_call:
	mov r0, #-1
	ldmia sp!, {r0-r12, pc}^ @;

undefined_instruction:
	@; save spot
	ldr sp, =UND_STACK @; stack == 1k
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

swi:
	@; save spot
	ldr sp, =SWI_STACK @; stack == 2K
	stmdb sp!, {r0-r12, lr}  @; lr is the instruction after swi

	@; call corresponding system call
	mov r0, #0
	mov r1, #1

	cmp r0, #nr_system_calls-1
	bhi bad_sys_call @; > 64
	bl sys_ledop

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

prefetch_abort:
	@; save spot	
	ldr sp, =PBT_STACK @; stack == 1K
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

data_abort:
	@; save spot	
	ldr sp, =DBT_STACK @; stack == 1K
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

not_used:
	@; save spot	
	ldr sp, =NUD_STACK @; stack == 1K
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

irq:
	@; save spot	
	ldr sp, =IRQ_STACK @; stack == 1K
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

fiq:
	@; save spot	
	ldr sp, =FIQ_STACK @; stack == 1K
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr


reset:
@; peripheral setting
@; tell CPU peripheral where is  
@; 256M -> 0x70000000 - 0x7FFFFFFF
	ldr r0, =0x70000000 @; SROM_BW
	orr r0,r0,#0x13
	mcr p15,0,r0,c15,c2,4

@; disable the watch dog
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]

@; exchange to SVC mode
	mrs r0, cpsr
	mov r0, #0xd3
	msr cpsr, r0 

@; set stack size == 8k
@; 8K is the MAX, but enough
	ldr sp, =1024 * 8 

@; initialization
	bl clock_init
	bl uart_init 
	bl sdram_init

@; copy data form nand to ddr
@; by call copy2ddr
	adr r0, _start  @; nand_start -> 0
	ldr r1, =_start
	sub r1, r1, #0x70000000 @; ddr_start -> 0x50000000

        ldr r2, =bss_start
	sub r2, r2, #0x70000000
	sub r2, r2, r1

	cmp r0, r1
	beq clean_bss

        bl copy2ddr
	cmp r0, #0     @; error
	bne halt

@; clean the bss
clean_bss:
	ldr r0, =bss_start
	sub r0, r0, #0x70000000
	ldr r1, =bss_end
	sub r1, r1, #0x70000000
	mov r3, #0
	cmp r0, r1
	beq on_ddr
clean_loop: 
	str r3, [r0], #4
	cmp r0, r1
	bne clean_loop

@; jump into DDR
on_ddr:
	@; initialize MMU
	bl mmu_init 

	@; exchange to user mode 
	mrs r0, cpsr
	mov r0, #0xd0
	msr cpsr, r0 

	ldr sp, =USR_STACK  @; follow the exception stack
	ldr pc, =main       @; pc == main link address  

halt:
	b halt

