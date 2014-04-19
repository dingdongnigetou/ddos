@;                 (C) 2014 JinDongHuang

.global _start
_start:
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

	msr cpsr, #0xdf

	@; set stack size == 8k
	@; 8K is the MAX, but enough
	ldr sp, = 1024 * 8 

	@; initialization
	bl clock_init  @; goto clock.c
	bl uart0_init  @; goto uart.c
	bl sdram_init  @; goto sdram.c
	bl main
@;	bl lcd_init    @; goto lcd.c

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

	@; clean the bss
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
	ldr pc, =main @; pc == main link address  
halt:
	b halt

