	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	powerMinusOne
	.syntax unified
	.thumb
	.thumb_func
	.type	powerMinusOne, %function
powerMinusOne:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	and	r0, r0, #1					;; r0 = n % 2
	movs	r1, #0
	orrs	r3, r0, r1
	vmov.f32	s15, #-1.0e+0
	vmov.f32	s0, #1.0e+0
	it	ne							;; if (r0 != 0) s0 = -1
	vmovne.f32	s0, s15 			;
	bx	lr
	.size	powerMinusOne, .-powerMinusOne
	.global	__aeabi_l2f
	.align	2
	.global	getNthElement
	.syntax unified
	.thumb
	.thumb_func
	.type	getNthElement, %function
getNthElement:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	vpush.64	{d8}
	and	r2, r0, #1					;; s15 = powerMinusOne(n) (inlined)
	movs	r3, #0					;
	orrs	r3, r2, r3				;
	vmov.f32	s15, #-1.0e+0		;
	vmov.f32	s16, #1.0e+0		;
	it	ne							;
	vmovne.f32	s16, s15			;; (-1)^n * 4
	vmov.f32	s15, #4.0e+0		;
	vmul.f32	s16, s16, s15		;
	adds	r0, r0, r0				;; 2n
	adcs	r1, r1, r1				
	adds	r0, r0, #1				;; 2n + 1
	adc	r1, r1, #0
	bl	__aeabi_l2f
	vmov	s15, r0					;; brackets calcualtion
	vdiv.f32	s0, s16, s15		;
	vldm	sp!, {d8}
	pop	{r3, pc}
	.size	getNthElement, .-getNthElement
	.align	2
	.global	picalculate
	.syntax unified
	.thumb
	.thumb_func
	.type	picalculate, %function
picalculate:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	vpush.64	{d8}
	movs	r4, #0					;; pi = 0
	movs	r5, #0					;; n = 0
	vldr.32	s16, .L12+8
	adr	r7, .L12					;; r6 = NUMBER_OF_ITERATIONS
	ldrd	r6, [r7] 				;
.L9:
	mov	r0, r4						;; r0 = pi
	mov	r1, r5						;; r1 = n
	bl	getNthElement				;; pi += getNthElement(n)
	vadd.f32	s16, s16, s0		;
	adds	r4, r4, #1				;; n ++
	adc	r5, r5, #0
	cmp	r5, r7
	it	eq
	cmpeq	r4, r6					;; if (n != NUMBER_OF_ITERATIONS) jmp .L9
	bne	.L9							;
	vmov.f32	s0, s16				;; s0 = s16 (end of cycle)
	vldm	sp!, {d8}
	pop	{r3, r4, r5, r6, r7, pc}
.L13:
	.align	3
.L12:
	.word	100000000
	.word	0
	.word	0
	.size	picalculate, .-picalculate
	.align	2
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	picalculate
	vcvt.f64.f32	d7, s0
	vmov	r2, r3, d7
	movw	r1, #:lower16:.LC0
	movt	r1, #:upper16:.LC0
	movs	r0, #1
	bl	__printf_chk
	movs	r0, #0
	pop	{r3, pc}
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Pi = %f\012\000"
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
