/*

Standalone C program, based on startup32-jmp.S, os_syscalls.c, and my_lib.c

tokcount-jmp.c :  Read a single line and report the number of tokens

Here a token in a string is defined as a maximal segment of consecutive
non-null non-whitespace characters, where whitespace characters are ' ',
'\t', '\n', and '\r'

This version is for starting from startup32-jmp.S, so:

  - Set global C variables:  int my_argc; char **my_argv, **my_envp;
  - Define main function as:  void mainprog(void) { ... };

Build commands:

  gcc -S -m32 -Wall -nostdlib -o os_syscalls.s os_syscalls.c
  gcc -S -m32 -Wall -nostdlib -o my_lib.s my_lib.c
  gcc -S -m32 -Wall -nostdlib -o tokcount-jmp.s tokcount-jmp.c

  as -32 -o startup32-jmp.o startup32-jmp.S
  as -32 -o os_syscalls.o os_syscalls.s
  as -32 -o my_lib.o my_lib.s
  as -32 -o tokcount-jmp.o tokcount-jmp.s

  ld -melf_i386 -nostdlib -o tokcount-jmp \
    startup32-jmp.o os_syscalls.o my_lib.o tokcount-jmp.o

Or as one command (not equivalent):

  gcc -m32 -Wall -nostdlib -o tokcount-jmp \
    startup32-jmp.S os_syscalls.c my_lib.c tokcount-jmp.c 

Or (best) use makefiles ...

*/

#include "os_syscalls.h"
#include "my_lib.h"

#define LINEBUFSIZE 256
#define MAXTOKS 256

char linebuf[LINEBUFSIZE+1];	/* Extra trailing byte for null char */

int my_argc;
char **my_argv, **my_envp;

void
mainprog(void)
{

	char *p;
	int r, n;

	p = linebuf;

	my_fprintf(1, "Enter command line:\n");

	/* Read a line */
	if ((r = os_read(0, p, LINEBUFSIZE)) < 0)
		os_exit(-r);

	linebuf[LINEBUFSIZE] = '\0';

	n = 0;
	while (1) {

        	/* Fast forward through any whitespaces */
		while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' )
			p++;

        	if (*p == '\0')
			break;
		else
			n++;

		if ( n + 1 >= MAXTOKS ) {
                	my_fprintf(2, "Too many tokens, truncating\n");
			break;
		}
	
		while (*p != '\0' && *p != ' ' && *p != '\t'
					&& *p != '\n' && *p != '\r')
			p++;

	}

	my_fprintf(1, "total number of tokens = %d\n", n);
	os_exit(0);

}


