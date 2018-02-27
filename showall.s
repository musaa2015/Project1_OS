	.file	"showall.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"Enter the environment variable you want to view\n"
.LC1:
	.string	"%s "
	.align 4
.LC2:
	.string	"Could not find Environment variable for user input\n"
	.text
	.globl	mainprog
	.type	mainprog, @function
mainprog:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	$1, -12(%ebp)
	movl	$.LC0, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	$1, (%esp)
	call	my_fprintf
	movl	$20, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	$0, (%esp)
	call	os_read
	movb	%al, -25(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -16(%ebp)
	jmp	.L2
.L4:
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-25(%ebp), %eax
	movl	%eax, (%esp)
	call	my_strcmp
	movl	%eax, -24(%ebp)
	cmpl	$0, -24(%ebp)
	je	.L3
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	$1, (%esp)
	call	my_fprintf
	movl	$0, -12(%ebp)
.L3:
	addl	$4, -16(%ebp)
.L2:
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L4
	cmpl	$0, -12(%ebp)
	je	.L5
	movl	$.LC2, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	$1, (%esp)
	call	my_fprintf
.L5:
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	mainprog, .-mainprog
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
