	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
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
powerMinusOne: 									;; same that with -O2
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	vmov.f32	s15, #-1.0e+0
	and	r0, r0, #1
	movs	r1, #0
	orrs	r3, r0, r1
	vmov.f32	s0, #1.0e+0
	it	ne
	vmovne.f32	s0, s15
	bx	lr
	.size	powerMinusOne, .-powerMinusOne
	.global	__aeabi_l2f
	.align	2
	.global	getNthElement
	.syntax unified
	.thumb
	.thumb_func
	.type	getNthElement, %function
getNthElement:									;; same that with -O2
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	vmov.f32	s0, #4.0e+0
	vpush.64	{d8}
	and	r2, r0, #1
	movs	r3, #0
	orrs	r3, r2, r3
	vmov.f32	s16, #-4.0e+0
	it	eq
	vmoveq.f32	s16, s0
	adds	r0, r0, r0
	adcs	r1, r1, r1
	adds	r0, r0, #1
	adc	r1, r1, #0
	bl	__aeabi_l2f
	vmov	s15, r0
	vdiv.f32	s0, s16, s15
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
	@ link register save eliminated.
	vmov.f32	s11, #4.0e+0
	movw	r2, #49665
	vldr.32	s0, .L13
	movt	r2, 3051
	movs	r0, #0
	movs	r1, #0
	movs	r3, #1
	push	{r4, r5}
	vmov.f32	s12, #-4.0e+0
.L9:
	vmov	s15, r3	@ int
	and	r4, r0, #1
	movs	r5, #0
	orrs	r4, r4, r5
	add	r3, r3, #2
	vcvt.f32.s32	s14, s15
	ite	ne							;; swaped, but total results are same
	vmovne.f32	s13, s12			;
	vmoveq.f32	s13, s11			;
	adds	r0, r0, #1
	adc	r1, r1, #0
	cmp	r3, r2
	vdiv.f32	s15, s13, s14
	vadd.f32	s0, s0, s15
	bne	.L9
	pop	{r4, r5}
	bx	lr
.L14:
	.align	2
.L13:
	.word	0
	.size	picalculate, .-picalculate
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	vmov.f32	s10, #4.0e+0
	movw	r2, #49665
	vldr.32	s15, .L19
	movt	r2, 3051
	push	{r3, r4, r5, lr}
	movs	r0, #0
	movs	r1, #0
	movs	r3, #1
	vmov.f32	s11, #-4.0e+0
.L16:
	vmov	s14, r3	@ int
	and	r4, r0, #1
	movs	r5, #0
	orrs	r4, r4, r5
	add	r3, r3, #2
	vcvt.f32.s32	s13, s14
	ite	ne
	vmovne.f32	s12, s11
	vmoveq.f32	s12, s10
	adds	r0, r0, #1
	adc	r1, r1, #0
	cmp	r3, r2
	vdiv.f32	s14, s12, s13
	vadd.f32	s15, s15, s14
	bne	.L16
	vcvt.f64.f32	d7, s15
	movw	r1, #:lower16:.LC0
	movs	r0, #1
	movt	r1, #:upper16:.LC0
	vmov	r2, r3, d7
	bl	__printf_chk
	movs	r0, #0
	pop	{r3, r4, r5, pc}
.L20:
	.align	2
.L19:
	.word	0
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Pi = %f\012\000"
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
