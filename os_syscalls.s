	.file	"os_syscalls.c"
	.text
	.type	syscallext, @function
syscallext:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$16, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
#APP
# 24 "os_syscalls.c" 1
	int $0x80
	
# 0 "" 2
#NO_APP
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	$16, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	syscallext, .-syscallext
	.globl	os_read
	.type	os_read, @function
os_read:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$3, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	os_read, .-os_read
	.globl	os_write
	.type	os_write, @function
os_write:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	os_write, .-os_write
	.globl	os_exit
	.type	os_exit, @function
os_exit:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	os_exit, .-os_exit
	.globl	os_close
	.type	os_close, @function
os_close:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$6, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	os_close, .-os_close
	.globl	os_open
	.type	os_open, @function
os_open:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	16(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$5, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	os_open, .-os_open
	.globl	os_execve
	.type	os_execve, @function
os_execve:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	16(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$11, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	os_execve, .-os_execve
	.globl	os_chdir
	.type	os_chdir, @function
os_chdir:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$12, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	os_chdir, .-os_chdir
	.globl	os_fork
	.type	os_fork, @function
os_fork:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$2, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	os_fork, .-os_fork
	.globl	os_waitpid
	.type	os_waitpid, @function
os_waitpid:
.LFB9:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	16(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$7, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	os_waitpid, .-os_waitpid
	.globl	os_pipe
	.type	os_pipe, @function
os_pipe:
.LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$42, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	os_pipe, .-os_pipe
	.globl	os_dup2
	.type	os_dup2, @function
os_dup2:
.LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$63, (%esp)
	call	syscallext
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	os_dup2, .-os_dup2
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
