@;                 (C) 2014 JinDongHuang

@; boot from the nand flash in s3c6410 
.global _start
_start:
	@; close the watch dog
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]
	
	@; set stack size == 4k
	ldr sp, =0x0C000000

	@; jump to main function
	bl  main 

halt:
	b halt

