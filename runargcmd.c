/*

runargcmd.c

Sample standalone C program baed on startup32.S, os_syscalls.c, and my_lib.c

This version is to be called from startup32.S, with arguments
on the stack, so the main function form can be one of:

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

Build commands:

   gcc -m32 -Wall -nostdlib -o runargcmd runargcmd.c startup32.S os_syscalls.c my_lib.c


*/

#include "os_syscalls.h"
#include "my_lib.h"

int mainprog(int argc, char **argv)
{
	os_execve(*(argv+1), argv+1, 0);
	return 0;
}
