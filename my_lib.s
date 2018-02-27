	.file	"my_lib.c"
	.text
	.globl	my_strcmp
	.type	my_strcmp, @function
my_strcmp:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
.L4:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L2
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L2
	movl	8(%ebp), %eax
	movzbl	(%eax), %edx
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	je	.L3
	jmp	.L2
.L3:
	addl	$1, 8(%ebp)
	addl	$1, 12(%ebp)
	jmp	.L4
.L2:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	my_strcmp, .-my_strcmp
	.type	itoa, @function
itoa:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$32, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	$10, -24(%ebp)
	cmpl	$100, 12(%ebp)
	jne	.L7
	cmpl	$0, 16(%ebp)
	jns	.L7
	movl	-8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -8(%ebp)
	movb	$45, (%eax)
	addl	$1, 8(%ebp)
	movl	16(%ebp), %eax
	negl	%eax
	movl	%eax, -20(%ebp)
	jmp	.L8
.L7:
	cmpl	$120, 12(%ebp)
	jne	.L8
	movl	$16, -24(%ebp)
.L8:
	movl	-24(%ebp), %ecx
	movl	-20(%ebp), %eax
	movl	$0, %edx
	divl	%ecx
	movl	%edx, %eax
	movl	%eax, -28(%ebp)
	movl	-8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -8(%ebp)
	cmpl	$9, -28(%ebp)
	jg	.L9
	movl	-28(%ebp), %edx
	addl	$48, %edx
	jmp	.L10
.L9:
	movl	-28(%ebp), %edx
	addl	$87, %edx
.L10:
	movb	%dl, (%eax)
	movl	-24(%ebp), %ebx
	movl	-20(%ebp), %eax
	movl	$0, %edx
	divl	%ebx
	movl	%eax, -20(%ebp)
	cmpl	$0, -20(%ebp)
	jne	.L8
	movl	-8(%ebp), %eax
	movb	$0, (%eax)
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	.L11
.L12:
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	movb	%al, -29(%ebp)
	movl	-16(%ebp), %eax
	movzbl	(%eax), %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	-16(%ebp), %eax
	movzbl	-29(%ebp), %edx
	movb	%dl, (%eax)
	addl	$1, -12(%ebp)
	subl	$1, -16(%ebp)
.L11:
	movl	-12(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jb	.L12
	addl	$32, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	itoa, .-itoa
	.type	fdputchar, @function
fdputchar:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$296, %esp
	movl	12(%ebp), %eax
	movb	%al, -284(%ebp)
	cmpl	$0, 8(%ebp)
	js	.L14
	cmpl	$255, 8(%ebp)
	jle	.L15
.L14:
	movl	$-1, %eax
	jmp	.L23
.L15:
	movl	8(%ebp), %eax
	movl	pend.1437(,%eax,4), %edx
	movl	8(%ebp), %eax
	movl	pstart.1436(,%eax,4), %eax
	movl	$256, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%ebp)
	cmpl	$255, -16(%ebp)
	je	.L17
	cmpl	$0, -16(%ebp)
	jle	.L18
	cmpl	$1, 16(%ebp)
	jne	.L18
.L17:
	movl	$0, -12(%ebp)
	jmp	.L19
.L20:
	movl	8(%ebp), %eax
	movl	pstart.1436(,%eax,4), %edx
	movl	-12(%ebp), %eax
	addl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	8(%ebp), %edx
	sall	$8, %edx
	addl	%edx, %eax
	addl	$infifo.1435, %eax
	movzbl	(%eax), %eax
	leal	-276(%ebp), %ecx
	movl	-12(%ebp), %edx
	addl	%ecx, %edx
	movb	%al, (%edx)
	addl	$1, -12(%ebp)
.L19:
	movl	-12(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jl	.L20
	movl	-16(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, 8(%esp)
	leal	-276(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	os_write
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	cmpl	-16(%ebp), %eax
	je	.L21
	movl	$-2, %eax
	jmp	.L23
.L21:
	movl	8(%ebp), %eax
	movl	pstart.1436(,%eax,4), %edx
	movl	-20(%ebp), %eax
	addl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, pstart.1436(,%eax,4)
.L18:
	cmpl	$1, 16(%ebp)
	jne	.L22
	movl	$0, %eax
	jmp	.L23
.L22:
	movl	8(%ebp), %eax
	movl	pend.1437(,%eax,4), %eax
	movl	8(%ebp), %edx
	sall	$8, %edx
	addl	%edx, %eax
	leal	infifo.1435(%eax), %edx
	movzbl	-284(%ebp), %eax
	movb	%al, (%edx)
	movl	8(%ebp), %eax
	movl	pend.1437(,%eax,4), %eax
	leal	1(%eax), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, pend.1437(,%eax,4)
	movl	$0, %eax
.L23:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	fdputchar, .-fdputchar
	.section	.rodata
.LC0:
	.string	"(null)"
	.text
	.globl	my_fprintf
	.type	my_fprintf, @function
my_fprintf:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$88, %esp
	leal	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	addl	$4, -12(%ebp)
	jmp	.L25
.L48:
	cmpb	$37, -13(%ebp)
	je	.L26
	movsbl	-13(%ebp), %eax
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	jmp	.L25
.L26:
	movl	$0, -28(%ebp)
	movl	$0, -32(%ebp)
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %eax
	movb	%al, -13(%ebp)
	cmpb	$37, -13(%ebp)
	jne	.L27
	movsbl	-13(%ebp), %eax
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	jmp	.L25
.L27:
	cmpb	$48, -13(%ebp)
	jne	.L28
	movl	$1, -28(%ebp)
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %eax
	movb	%al, -13(%ebp)
	jmp	.L29
.L28:
	jmp	.L29
.L31:
	movl	-32(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movsbl	-13(%ebp), %eax
	addl	%edx, %eax
	subl	$48, %eax
	movl	%eax, -32(%ebp)
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %eax
	movb	%al, -13(%ebp)
.L29:
	cmpb	$47, -13(%ebp)
	jle	.L30
	cmpb	$57, -13(%ebp)
	jle	.L31
.L30:
	movsbl	-13(%ebp), %eax
	cmpl	$115, %eax
	je	.L33
	cmpl	$115, %eax
	jg	.L34
	testl	%eax, %eax
	je	.L35
	cmpl	$100, %eax
	je	.L36
	jmp	.L32
.L34:
	cmpl	$117, %eax
	je	.L36
	cmpl	$120, %eax
	je	.L36
	jmp	.L32
.L35:
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 12(%ebp)
	jmp	.L25
.L36:
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %edx
	movsbl	-13(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	leal	-72(%ebp), %eax
	movl	%eax, (%esp)
	call	itoa
	leal	-72(%ebp), %eax
	movl	%eax, -20(%ebp)
	jmp	.L37
.L33:
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	cmpl	$0, -20(%ebp)
	jne	.L37
	movl	$.LC0, -20(%ebp)
.L37:
	movl	-20(%ebp), %eax
	movl	%eax, -24(%ebp)
	jmp	.L38
.L39:
	addl	$1, -24(%ebp)
.L38:
	movl	-24(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L39
	cmpl	$0, -28(%ebp)
	je	.L40
	movl	$48, %eax
	jmp	.L41
.L40:
	movl	$32, %eax
.L41:
	movb	%al, -13(%ebp)
	jmp	.L42
.L43:
	movsbl	-13(%ebp), %eax
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	addl	$1, -24(%ebp)
.L42:
	movl	-32(%ebp), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	cmpl	-24(%ebp), %eax
	ja	.L43
	jmp	.L44
.L45:
	movl	-20(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -20(%ebp)
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
.L44:
	movl	-20(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L45
	jmp	.L25
.L32:
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	%eax, 8(%esp)
	movl	$120, 4(%esp)
	leal	-72(%ebp), %eax
	movl	%eax, (%esp)
	call	itoa
	leal	-72(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	$0, 8(%esp)
	movl	$91, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	movl	$0, 8(%esp)
	movl	$120, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	jmp	.L46
.L47:
	movl	-20(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -20(%ebp)
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
.L46:
	movl	-20(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L47
	movl	$0, 8(%esp)
	movl	$93, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	nop
.L25:
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %eax
	movb	%al, -13(%ebp)
	cmpb	$0, -13(%ebp)
	jne	.L48
	movl	$1, 8(%esp)
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	fdputchar
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	my_fprintf, .-my_fprintf
	.local	pend.1437
	.comm	pend.1437,1024,32
	.local	pstart.1436
	.comm	pstart.1436,1024,32
	.local	infifo.1435
	.comm	infifo.1435,65536,32
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
