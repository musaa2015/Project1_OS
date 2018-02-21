/*

hello.c

Sample standalone C program baed on startup32.S, os_syscalls.c, and my_lib.c

This version is to be called from startup32.S, with arguments
on the stack, so the main function form can be one of:

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

Build commands:

  gcc -S -m32 -Wall -nostdlib -o os_syscalls.s os_syscalls.c
  gcc -S -m32 -Wall -nostdlib -o my_lib.s my_lib.c
  gcc -S -m32 -Wall -nostdlib -o hello.s hello.c

  as -32 -o startup32.o startup32.S
  as -32 -o os_syscalls.o os_syscalls.s
  as -32 -o my_lib.o my_lib.s
  as -32 -o hello.o hello.s

  ld -melf_i386 -nostdlib -o hello startup32.o os_syscalls.o my_lib.o hello.o

Or as one command (not equivalent):

  gcc -m32 -Wall -nostdlib -o hello hello.c startup32.S os_syscalls.c my_lib.c

Or (best), use makefiles ...

*/

#include "os_syscalls.h"
#include "my_lib.h"

int mainprog(void)
{
	my_fprintf(1, "hello, world!\n");
	return 0;
}
