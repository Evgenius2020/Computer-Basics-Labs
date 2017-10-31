	.file	"main.c"
	.text
	.globl	powerMinusOne
	.type	powerMinusOne, @function
powerMinusOne:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx

	subl	$8, %esp
	movl	8(%ebp), %ecx			## Doing nothing, srlsy.
	movl	%ecx, -16(%ebp)			#
	movl	12(%ebp), %ecx			#
	movl	%ecx, -12(%ebp)			#
	movl	-16(%ebp), %ecx			# 
	movl	-12(%ebp), %ebx			#

	movl	%ecx, %esi			## eax = n % 2   // (n && 1)
	andl	$1, %esi			#
	movl	%esi, %eax			#

	andl	$0, %ebx			## Dead code
	movl	%ebx, %edx			# 
	orl	%edx, %eax			#

	testl	%eax, %eax			## getting ZF
	jne	.L2				## if (!ZF)
	fld1					## push(1.0)
	jmp	.L3
.L2:
	fld1					## push(-1.0)
	fchs					#
.L3:
	addl	$8, %esp			## leave
	popl	%ebx				#
	popl	%esi				#
	popl	%ebp				#
	ret
	.size	powerMinusOne, .-powerMinusOne
	.globl	getNthElement
	.type	getNthElement, @function
getNthElement:
	pushl	%ebp
	movl	%esp, %ebp

	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	pushl	-4(%ebp)			## Dead code
	pushl	-8(%ebp) 			#

	call	powerMinusOne

	addl	$8, %esp
	flds	.LC3				## push((4.0) * powerMinusOne(n))
	fmulp	%st, %st(1)			#
	movl	-8(%ebp), %eax			## Dead code
	movl	-4(%ebp), %edx			#
	shldl	$1, %eax, %edx			#
	addl	%eax, %eax			## %eax = 2 * n + 1
	addl	$1, %eax			#
	adcl	$0, %edx			
	movl	%eax, -24(%ebp)			## rightBrasket = eax
	movl	%edx, -20(%ebp)
	fildq	-24(%ebp)			## push(rightBrasket) (with sign)
	fstps	-12(%ebp)			## less code 
	flds	-12(%ebp)			#
	fdivrp	%st, %st(1)			## push(leftBarsket / rightBrasket)
	leave
	ret
	.size	getNthElement, .-getNthElement
	.globl	picalculate
	.type	picalculate, @function
picalculate:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp

	fldz					## pi = 0.0
	fstps	-12(%ebp)			#
	movl	$0, -8(%ebp)			## n = 0
	movl	$0, -4(%ebp)			## `n = 0 (CF)
	jmp	.L7
.L8:
	pushl	-4(%ebp)			## push(`n))
	pushl	-8(%ebp)			## push(n)

	call	getNthElement

	addl	$8, %esp			## %esp += 8
	flds	-12(%ebp)			## push(pi)
	faddp	%st, %st(1)			## push(pop() + getNthElement(n))
	fstps	-12(%ebp)			## pi = pop()
	addl	$1, -8(%ebp)			## n += 1
	adcl	$0, -4(%ebp)			## `n += CF
.L7:
	cmpl	$0, -4(%ebp)			
	js	.L8				## if (0 < `n)
	cmpl	$0, -4(%ebp)
	jg	.L11				## if (0 > `n)
	cmpl	$99999999, -8(%ebp)		
	jbe	.L8				## if (number_of_iterations >= n)
.L11:
	flds	-12(%ebp)			## push(pi)
	leave
	ret
	.size	picalculate, .-picalculate
	.section	.rodata
.LC5:
	.string	"Pi = %f\n"
	.text
	.globl	main
	.type	main, @function
main:
	leal	4(%esp), %ecx			## %ecx = esp + 4
	andl	$-16, %esp
	pushl	-4(%ecx)			## ST(0) = ecx - 4
	pushl	%ebp				## ST(0) = ebp
	movl	%esp, %ebp			## ebp = esp
	pushl	%ecx				## ST(0) = ecx
	subl	$36, %esp			## esp -= 36

	call	picalculate			

	fstps	-28(%ebp)			## pi = pop(ST)
	movl	-28(%ebp), %eax			## %eax = pi
	movl	%eax, -12(%ebp)			## %ebp - 12 = pi
	flds	-12(%ebp)			## ST(0) = pi
	subl	$4, %esp			## %esp - 4
	leal	-8(%esp), %esp			## %esp -= 8
	fstpl	(%esp)				## %esp = pop(st)
	pushl	$.LC5				## st(0) = "Pi = %f\n"

	call	printf				

	addl	$16, %esp			## %exp += 16
	movl	$0, %eax			## %eax = 0
	movl	-4(%ebp), %ecx			## %ecx = %(ebp - 4)
	leave
	leal	-4(%ecx), %esp			## %exp = ecx - 4
	ret
	.size	main, .-main
	.section	.rodata
	.align 4
.LC3:
	.long	1082130432
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
