	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
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
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r7}
	sub	sp, sp, #8
	add	r7, sp, #0
	strd	r0, [r7]
	ldrd	r3, [r7]
	mov	r1, #1
	mov	r2, #0
	and	r3, r3, r1
	and	r4, r4, r2
	orrs	r3, r3, r4
	bne	.L2
	mov	r3, #1065353216
	b	.L3
.L2:
	mov	r3, #0
	movt	r3, 49024
.L3:
	vmov	s15, r3
	vmov.f32	s0, s15
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r4, r7}
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
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r7, lr}
	vpush.64	{d8}
	sub	sp, sp, #12
	add	r7, sp, #0
	strd	r0, [r7]
	ldrd	r0, [r7]
	bl	powerMinusOne
	vmov.f32	s14, s0
	vmov.f32	s15, #4.0e+0
	vmul.f32	s16, s14, s15
	ldrd	r3, [r7]
	adds	r3, r3, r3
	adc	r4, r4, r4
	adds	r3, r3, #1
	adc	r4, r4, #0
	mov	r0, r3
	mov	r1, r4
	bl	__aeabi_l2f
	vmov	s14, r0
	vdiv.f32	s15, s16, s14
	vmov.f32	s0, s15
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	vldm	sp!, {d8}
	pop	{r4, r7, pc}
	.size	getNthElement, .-getNthElement
	.align	2
	.global	picalculate
	.syntax unified
	.thumb
	.thumb_func
	.type	picalculate, %function
picalculate:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r7, lr}
	sub	sp, sp, #20
	add	r7, sp, #0
	mov	r3, #0
	str	r3, [r7, #4]	@ float
	mov	r3, #0
	mov	r4, #0
	strd	r3, [r7, #8]
	b	.L7
.L8:
	ldrd	r0, [r7, #8]
	bl	getNthElement
	vmov.f32	s14, s0
	vldr.32	s15, [r7, #4]
	vadd.f32	s15, s15, s14
	vstr.32	s15, [r7, #4]
	ldrd	r3, [r7, #8]
	adds	r3, r3, #1
	adc	r4, r4, #0
	strd	r3, [r7, #8]
.L7:
	ldrd	r3, [r7, #8]
	adr	r2, .L10
	ldrd	r1, [r2]
	cmp	r1, r3
	sbcs	r3, r2, r4
	bge	.L8
	ldr	r3, [r7, #4]	@ float
	vmov	s15, r3
	vmov.f32	s0, s15
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	pop	{r4, r7, pc}
.L11:
	.align	3
.L10:
	.word	99999999
	.word	0
	.size	picalculate, .-picalculate
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Pi = %f\012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	bl	picalculate
	vstr.32	s0, [r7, #4]
	vldr.32	s15, [r7, #4]
	vcvt.f64.f32	d7, s15
	vmov	r2, r3, d7
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
