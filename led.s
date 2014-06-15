	.cpu arm1176jzf-s
	.eabi_attribute 27, 3
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"led.c"
	.text
	.align	2
	.global	ledop
	.type	ledop, %function
ledop:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, fp}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r3, #0
#APP
@ 10 "lib/led.c" 1
	mov r3, r3
swi 0

@ 0 "" 2
	str	r4, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	blt	.L2
	ldr	r3, [fp, #-8]
	b	.L3
.L2:
	mvn	r3, #0
.L3:
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {r4, fp}
	bx	lr
	.size	ledop, .-ledop
	.align	2
	.global	test
	.type	test, %function
test:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, fp}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #1
#APP
@ 11 "lib/led.c" 1
	mov r3, r3
swi 0

@ 0 "" 2
	str	r4, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	blt	.L5
	ldr	r3, [fp, #-8]
	b	.L6
.L5:
	mvn	r3, #0
.L6:
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {r4, fp}
	bx	lr
	.size	test, .-test
	.ident	"GCC: (ctng-1.8.1-FA) 4.5.1"
	.section	.note.GNU-stack,"",%progbits
