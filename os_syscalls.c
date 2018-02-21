/*

File os_syscalls.c

Standalone C system call wrappers for linux/i386.

The code here uses assembly to perform the actual syscalls,
and provides user programs with C wrapper functions such
as os_exit(), os_write(), etc, which have a far more portable
format (like the C library wrappers for system calls).

*/

#ifndef __i386__
# error Unsupported arch
#endif

/* The assembly back end */
static int
syscallext(unsigned long syscallnum,
	unsigned long arg1, unsigned long arg2, unsigned long arg3)
{
	int ret;
	asm volatile (
		"int $0x80\n\t"
		: "=a" (ret)
		: "a" (syscallnum), "b" (arg1), "c" (arg2), "d" (arg3)
	);
	return ret;
}

/* C wrapper functions for system calls */
int
os_read(unsigned int fd, char *buf, unsigned int len)
{
	return syscallext(3,
		(unsigned long) fd,
		(unsigned long) buf,
		(unsigned long) len);
}

int
os_write(unsigned int fd, char *buf, unsigned int len)
{
	return syscallext(4,
		(unsigned long) fd,
		(unsigned long) buf,
		(unsigned long) len);
}

int
os_exit(int exitcode)
{
	return syscallext(1,
		(unsigned long) exitcode,
		0,
		0);
}

int
os_close(int fd)
{
	return syscallext(6,
		(unsigned long) fd,
		0,
		0);
}

int
os_open(char *pathname, int flags, int mode)
{
	return syscallext(5,
		(unsigned long) pathname,
		(unsigned long) flags,
		(unsigned long) mode);
}

