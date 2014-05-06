@;                 (C) 2014 Jindong Huang

.global _start 
_start:

	b reset  @; 0x00
	ldr pc, =undefined_instruction @; 0x04 miss undefined instruction 
	ldr pc, _swi            @; 0x08 when run swi      
	ldr pc, _prefetch_abort @; 0x0C prefetch abort exception
	ldr pc, _data_abort     @; 0x10 data access exception
	ldr pc, _not_used       @; 0x14 not used 
	ldr pc, _irq            @; 0x18 interrupt exception 
	ldr pc, _fiq            @; 0x1C fast interrupt exception 


_swi:
	.word swi
_prefetch_abort:
	.word prefetch_abort
_data_abort:
	.word data_abort
_not_used:
	.word not_used
_irq:
	.word irq
_fiq:
	.word fiq

undefined_instruction:
	@; save spot
	ldr sp, =0x56000000
	stmdb sp!, {r0-r12, lr}

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

swi:
	@; save spot
	ldr sp, =0x55000000
	stmdb sp!, {r0-r12, lr}  @; lr is the instruction after swi

	@; handle exception

	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr

prefetch_abort:
	b halt

data_abort:
	b halt

not_used:
	b halt

irq:
	@; save spot
	ldr sp, =0x54000000
	sub lr, lr, #4
	stmdb sp!, {r0-r12, lr}

	@; handle exception
	
	@; resume
	ldmia sp!, {r0-r12, pc}^ @; ^ is resume spsr to cpsr


fiq:

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

	@; set stack size == 8k
	@; 8K is the MAX, but enough
	ldr sp, = 1024 * 8 

	@; initialization
	bl clock_init
	bl uart_init 
	bl sdram_init

	@; copy data form nand to ddr
	@; by call copy2ddr
	adr r0, _start  @; nand_start -> 0
	ldr r1, =_start @; ddr_start -> 0x50000000

	@; len
	ldr r2, = bss_start	
	sub r2, r2, r1

	cmp r0, r1
	beq clean_bss

	bl copy2ddr
	cmp r0, #0     @; error
	bne halt

	ldr r0, =bss_start
	ldr r1, =bss_end
	mov r3, #0
	cmp r0, r1
	beq on_ddr

	@; clean bss
clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	mov r3, #0
	cmp r0, r1
	beq on_ddr
clean_loop:
	str r3, [r0], #4
	cmp r0, r1	
	bne clean_loop	

	@; jump into DDR
on_ddr:
	ldr pc, = main       @; pc == main link address  
halt:
	b halt

