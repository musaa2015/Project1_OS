/*

Standalone C program based on startup32, os_syscalls.c, and my_lib.c

tokcount.c :  Read a single line and report the number of tokens

Here a token in a string is defined as a maximal segment of consecutive
non-null non-whitespace characters, where whitespace characters are ' ',
'\t', '\n', and '\r'

This version is to be called from startup32.S, with arguments
on the stack, so the main function form can be one of:

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

Build commands:

  gcc -S -m32 -Wall -nostdlib -o os_syscalls.s os_syscalls.c
  gcc -S -m32 -Wall -nostdlib -o my_lib.s my_lib.c
  gcc -S -m32 -Wall -nostdlib -o tokcount.s tokcount.c

  as -32 -o startup32.o startup32.S
  as -32 -o os_syscalls.o os_syscalls.s
  as -32 -o my_lib.o my_lib.s
  as -32 -o tokcount.o tokcount.s

  ld -melf_i386 -nostdlib -o tokcount \
    startup32.o os_syscalls.o my_lib.o tokcount.o

Or as one command (not equivalent):

  gcc -m32 -Wall -nostdlib -o tokcount \
    tokcount.c startup32.S os_syscalls.c my_lib.c

Or (best), use makefiles ...

*/

#include "os_syscalls.h"
#include "my_lib.h"

#define LINEBUFSIZE 256
#define MAXTOKS 256

char linebuf[LINEBUFSIZE+1];	/* Extra trailing byte for null char */

int
mainprog(void)
{

	char *p;
	int r, n;

	p = linebuf;

	my_fprintf(1, "Enter command line:\n");

	/* Read a line */
	if ((r = os_read(0, p, LINEBUFSIZE)) < 0)
		return -r;

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
	return 0;

}


