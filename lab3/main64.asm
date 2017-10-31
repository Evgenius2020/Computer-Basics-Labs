	.file	"main.c"
	.text
	.globl	powerMinusOne
	.type	powerMinusOne, @function
powerMinusOne:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)			## rax = n
	movq	-8(%rbp), %rax			#
	andl	$1, %eax			## (n % 2) != 0?
	testq	%rax, %rax			#
	jne	.L2				#
	movss	.LC0(%rip), %xmm0		## result = 1
	jmp	.L3
.L2:
	movss	.LC1(%rip), %xmm0		## result = -1
.L3:
	popq	%rbp
	ret
	.size	powerMinusOne, .-powerMinusOne
	.globl	getNthElement
	.type	getNthElement, @function
getNthElement:
	pushq	%rbp				## Stackframe actions (8 bytes for local variables)
	movq	%rsp, %rbp			#
	subq	$8, %rsp			#
	movq	%rdi, -8(%rbp)			## n from piCalculate()
	movq	-8(%rbp), %rax			## transfering n to powerMinusOne()
	movq	%rax, %rdi			#
	call	powerMinusOne
	movaps	%xmm0, %xmm1			## -1 * 4
	movss	.LC2(%rip), %xmm0		#
	mulss	%xmm1, %xmm0			#
	movq	-8(%rbp), %rax			## n + n + 1
	addq	%rax, %rax			#
	addq	$1, %rax			#
	pxor	%xmm1, %xmm1			## braskets calculation
	cvtsi2ssq	%rax, %xmm1		#
	divss	%xmm1, %xmm0			#
	leave
	ret
	.size	getNthElement, .-getNthElement
	.globl	picalculate
	.type	picalculate, @function
picalculate:
	pushq	%rbp				## Stackframe actions
	movq	%rsp, %rbp			#
	subq	$16, %rsp			#
	pxor	%xmm0, %xmm0			## pi = 0
	movss	%xmm0, -12(%rbp)		#
	movq	$0, -8(%rbp)			## n = 0
	jmp	.L7
.L8:
	movq	-8(%rbp), %rax			## transfering n to getNthElement()
	movq	%rax, %rdi			#
	call	getNthElement			## pi += getNthElement(n)
	movaps	%xmm0, %xmm1			#
	movss	-12(%rbp), %xmm0		#
	addss	%xmm1, %xmm0			#
	movss	%xmm0, -12(%rbp)		#
	addq	$1, -8(%rbp)			## n++
.L7:
	cmpq	$99999999, -8(%rbp)		## jmp .L8 if (number_of_iteraions - 1) <= n
	jle	.L8				#
	movss	-12(%rbp), %xmm0		## result = pi
	leave
	ret
	.size	picalculate, .-picalculate
	.section	.rodata
.LC4:
	.string	"Pi = %f\n"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp				## Stackframe actions
	movq	%rsp, %rbp			#
	subq	$16, %rsp			#
	movl	$0, %eax			
	call	picalculate			## pi = piCalculate()
	movd	%xmm0, %eax			#
	movl	%eax, -4(%rbp)			#
	cvtss2sd	-4(%rbp), %xmm0		## printf("Pi = %f\n", pi)
	movl	$.LC4, %edi			#
	movl	$1, %eax			#
	call	printf				#
	movl	$0, %eax			
	leave
	ret
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1065353216
	.align 4
.LC1:
	.long	3212836864
	.align 4
.LC2:
	.long	1082130432
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
