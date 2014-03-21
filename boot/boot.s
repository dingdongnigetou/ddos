@;                 (C) 2014 JinDongHuang

@; boot from the nand flash in s3c6410 
.globl _start
_start:
	@; peripheral setting
	ldr r0, =0x70000000
	orr r0, r0, #0x13
	mcr p15, 0, r0, c15, c2, 4

	@; close the watch dog
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]
	
	@; light the first led
	ldr r0, =0x7F008800
	mov r1, #0x00010000
	str r1, [r0]
	ldr r0, =0x7F008808
	mov r1, #0
	str r1, [r0]

halt:
	b halt

