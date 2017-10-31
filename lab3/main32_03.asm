	.file	"main.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	powerMinusOne
	.type	powerMinusOne, @function
powerMinusOne:
	fld1
	testb	$1, 4(%esp)
	fld1				
	fchs				
	fcmove	%st(1), %st
	fstp	%st(1)			
	ret
	.size	powerMinusOne, .-powerMinusOne
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	getNthElement
	.type	getNthElement, @function
getNthElement:
	subl	$20, %esp
	movl	24(%esp), %eax		## eax = n
	flds	.LC5			## push(4)
	movl	28(%esp), %edx		## 
	flds	.LC4			## push(-4)
	movl	%eax, %ecx		## very smart changing between 4 and -4  
	andl	$1, %ecx		# 
	testl	%ecx, %ecx		#
	fcmovne	%st(1), %st		#
	fstp	%st(1)			#
	shldl	$1, %eax, %edx
	addl	%eax, %eax		## edx = eax*2 + 1
	addl	$1, %eax		#
	adcl	$0, %edx		
	movl	%eax, (%esp)		
	movl	%edx, 4(%esp)		
	fildq	(%esp)			# push(edx)
	addl	$20, %esp
	fdivrp	%st, %st(1)		## st(0) = st(1) / st(0)
	ret
	.size	getNthElement, .-getNthElement
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4,,15
	.globl	picalculate
	.type	picalculate, @function
picalculate:
	pushl	%esi
	pushl	%ebx
	fldz				## push(0.0)
	movl	$1, %eax		## n = 1
	xorl	%ecx, %ecx		## ecx = 0
	xorl	%ebx, %ebx		## ebx = 0
	subl	$12, %esp
	movl	.LC4, %esi		## esi = -4
	.p2align 4,,10
	.p2align 3
.L11:
	flds	.LC5			## push(4)
	movl	%esi, 4(%esp)		## pi = -4
	movl	%ecx, %edx		## edx = ecx & 1
	andl	$1, %edx		#
	flds	4(%esp)			## push(pi)
	testl	%edx, %edx
	movl	%eax, 4(%esp)		## pi = n
	fcmovne	%st(1), %st		## push(4) if ...
	fstp	%st(1)			#
	addl	$1, %ecx		## ecx++
	adcl	$0, %ebx		## ebx += CF
	addl	$2, %eax		## n += 2
	cmpl	$200000001, %eax
	fildl	4(%esp)			## push(pi)
	fdivrp	%st, %st(1)		## pi += (-4)^ecx 
	faddp	%st, %st(1)		#
	jne	.L11
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	picalculate, .-picalculate
	.section	.text.unlikely
.LCOLDE8:
	.text
.LHOTE8:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC9:
	.string	"Pi = %f\n"
	.section	.text.unlikely
.LCOLDB10:
	.section	.text.startup,"ax",@progbits
.LHOTB10:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	fldz				## push(0.0)
	movl	$1, %eax		## n = 1
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	xorl	%ebx, %ebx		# ebx = 0
	xorl	%ecx, %ecx		# ecx = 0
	subl	$28, %esp
	movl	.LC4, %esi		## esi = -4
	.p2align 4,,10
	.p2align 3
.L18:
	flds	.LC5			## push (4)
	movl	%esi, -28(%ebp)
	movl	%ecx, %edx		## edx = ecx & 1
	andl	$1, %edx		#
	flds	-28(%ebp)		## push(-4)
	testl	%edx, %edx
	movl	%eax, -28(%ebp)		## pi = n
	fcmovne	%st(1), %st
	fstp	%st(1)
	addl	$1, %ecx		## ecx++
	adcl	$0, %ebx		## ebx += CF
	addl	$2, %eax		## n += 2
	cmpl	$200000001, %eax
	fildl	-28(%ebp)		## push (pi)
	fdivrp	%st, %st(1)		## pi = ...
	faddp	%st, %st(1)		#
	jne	.L18

	subl	$8, %esp
	fstpl	(%esp)
	pushl	$.LC9
	pushl	$1

	call	__printf_chk

	addl	$16, %esp
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE10:
	.section	.text.startup
.LHOTE10:
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC4:
	.long	1082130432
	.align 4
.LC5:
	.long	3229614080
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
