	.file	"main.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	powerMinusOne
	.type	powerMinusOne, @function
powerMinusOne:
	andl	$1, %edi			## n && 1 (checks ZF)
	movss	.LC0(%rip), %xmm0		## result = 1
	je	.L2				## using ZF
	movss	.LC1(%rip), %xmm0		## result = -1
.L2:
	rep ret
	.size	powerMinusOne, .-powerMinusOne
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	getNthElement
	.type	getNthElement, @function
getNthElement:
	testb	$1, %dil			## xmm0 = (n % 2 != 1) ? 4 : -4
	movss	.LC4(%rip), %xmm0		#
	jne	.L7				#
	movss	.LC3(%rip), %xmm0		#
.L7:
	pxor	%xmm1, %xmm1			## xmm1 = n + n + 1 
	leaq	1(%rdi,%rdi), %rax		#
	cvtsi2ssq	%rax, %xmm1		#
	divss	%xmm1, %xmm0			## braskets calculation
	ret
	.size	getNthElement, .-getNthElement
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	picalculate
	.type	picalculate, @function
picalculate:
	pxor	%xmm0, %xmm0			## pi = 0
	movl	$1, %edx			## rdx = 1
	xorl	%eax, %eax			## rax = 0
	movss	.LC4(%rip), %xmm3		## xmm3 = -4
	movss	.LC3(%rip), %xmm4	 	## xmm4 = 4
	.p2align 4,,10
	.p2align 3
.L12:
	testb	$1, %al				## xmm1 = (rax % 2 != 1) ? 4 : -4
	movaps	%xmm3, %xmm1			#
	jne	.L11				#
	movaps	%xmm4, %xmm1			#
.L11:
	pxor	%xmm2, %xmm2			## xmm2 = 0
	addq	$1, %rax			## rax++
	cvtsi2ssq	%rdx, %xmm2		## xmm2 = rdx
	addq	$2, %rdx			## rdx += 2
	cmpq	$100000000, %rax 
	divss	%xmm2, %xmm1			## pi += xmm1 \ xmm2
	addss	%xmm1, %xmm0			#
	jne	.L12				## if (rax != number of steps) jmp
	rep ret	
	.size	picalculate, .-picalculate
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC8:
	.string	"Pi = %f\n"
	.section	.text.unlikely
.LCOLDB9:
	.section	.text.startup,"ax",@progbits
.LHOTB9:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
	pxor	%xmm1, %xmm1			## pi = 0
	movl	$1, %edx			## rdx = 1
	xorl	%eax, %eax			## n = 0
	movss	.LC4(%rip), %xmm3		## xmm3 = -4
	movss	.LC3(%rip), %xmm4		## xmm4 = 4
	.p2align 4,,10
	.p2align 3
.L17:
	testb	$1, %al				## xmm0 = (n % 2 != 1) ? 4 : -4
	movaps	%xmm3, %xmm0			#
	jne	.L16				#
	movaps	%xmm4, %xmm0			#
.L16:
	pxor	%xmm2, %xmm2			## xmm2 = 0
	addq	$1, %rax			## n++
	cvtsi2ssq	%rdx, %xmm2		## xmm2 = rdx
	addq	$2, %rdx			## rdx += 2
	cmpq	$100000000, %rax		
	divss	%xmm2, %xmm0			## pi += (-4)^n / `rdx
	addss	%xmm0, %xmm1			#
	jne	.L17				## if (n != number_of_iterations) jmp
	pxor	%xmm0, %xmm0
	subq	$8, %rsp
	movl	$.LC8, %esi
	movl	$1, %edi
	movl	$1, %eax
	cvtss2sd	%xmm1, %xmm0		## xmm0 = pi
	call	__printf_chk
	xorl	%eax, %eax
	addq	$8, %rsp
	ret
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE9:
	.section	.text.startup
.LHOTE9:
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1065353216
	.align 4
.LC1:
	.long	3212836864
	.align 4
.LC3:
	.long	1082130432
	.align 4
.LC4:
	.long	3229614080
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
