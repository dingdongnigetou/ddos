@;                 (C) 2014 JinDongHuang

@; boot from the nand flash in s3c6410 
.global _start
_start:
	@; peripheral setting
	ldr r0, =0x70000000 @; SROM_BW
	orr r0,r0,#0x13
	mcr p15,0,r0,c15,c2,4

	@; set stack size == 4k
	ldr sp, =1024 * 4

	bl disable_watch_dog
	bl clock_init
_trampline:
	bl  main 
	b   _trampline

halt:
	b halt

