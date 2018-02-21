/*

hello-jmp.c

Sample standalone C program baed on startup32-jmp.S, os_syscalls.c, my_lib.c

This version is for starting from startup32-jmp.S, so:

  - Set global C variables:  int my_argc; char **my_argv, **my_envp;
  - Define main function as:  void mainprog(void) { ... };

Build commands:

  gcc -S -m32 -Wall -nostdlib -o os_syscalls.s os_syscalls.c
  gcc -S -m32 -Wall -nostdlib -o my_lib.s my_lib.c
  gcc -S -m32 -Wall -nostdlib -o hello-jmp.s hello-jmp.c

  as -32 -o startup32-jmp.o startup32-jmp.S
  as -32 -o os_syscalls.o os_syscalls.s
  as -32 -o my_lib.o my_lib.s
  as -32 -o hello-jmp.o hello-jmp.s

  ld -melf_i386 -nostdlib -o hello-jmp \
    startup32-jmp.o os_syscalls.o my_lib.o hello-jmp.o

Or as one command (not equivalent):

  gcc -m32 -Wall -nostdlib -o hello-jmp \
    hello-jmp.c startup32-jmp.S os_syscalls.c my_lib.c

Or (best), use makefiles ...

*/

#include "os_syscalls.h"
#include "my_lib.h"

int my_argc;
char **my_argv, **my_envp;

void
mainprog(void)
{
	my_fprintf(1, "hello, world!\n");
	os_exit(0);
}

