/*

Standalone C cat program, based on startup32.S, os_syscalls.c, and my_lib.c

This version is to be called from startup32.S, with arguments
on the stack, so the main function form can be one of:

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

Build commands:

  gcc -S -m32 -Wall -nostdlib -o os_syscalls.s os_syscalls.c
  gcc -S -m32 -Wall -nostdlib -o my_lib.s my_lib.c
  gcc -S -m32 -Wall -nostdlib -o mycat.s mycat.c

  as -32 -o startup32.o startup32.S
  as -32 -o os_syscalls.o os_syscalls.s
  as -32 -o my_lib.o my_lib.s
  as -32 -o mycat.o mycat.s

  ld -melf_i386 -nostdlib -o mycat startup32.o os_syscalls.o my_lib.o mycat.o

Or as one command (not equivalent):

  gcc -m32 -Wall -nostdlib -o mycat mycat.c startup32.S os_syscalls.c my_lib.c

Or (best), use makefiles ...

*/

#include "os_syscalls.h"
#include "my_lib.h"

#define LINEBUFSIZE 128

/* #include <asm-generic/fcntl.h> */
#define O_RDONLY        00000000
#define O_WRONLY        00000001
#define O_RDWR          00000002

char openerr[] = "ERROR:  Open returned negative!\n";
char readerr[] = "ERROR:  Read returned negative!\n";
char writeerr[] = "ERROR:  Write returned negative!\n";

/*
  This function will be called with readret <= 0 (but we cover all cases).
  If readret == 0 we have normal exit, and if readret < 0 we had a read error.
*/
void
terminate(int readret)
{

	if (readret == 0)				/* Got EOF : Normal exit */
		os_exit(0);
	else if (readret < 0) {			/* Had a read ERROR */
		my_fprintf(2, "%s", readerr);
		os_exit(-readret);
	} else							/* Should not happen */
		os_exit(0);

}

/*
The cat routine:  Copy from fdin to fdout
*/
int
fdcat(int fdin, int fdout)
{

	char buf[8192];
	int r, w;

	while ((r = os_read(fdin, buf, LINEBUFSIZE)) > 0) {
		w = os_write(fdout, buf, r);
		if (w != r) {					/* Write error */
			my_fprintf(2, "%s", writeerr);
			if (w < 0)
				os_exit(-w);
			else
				os_exit(-1);
		}
	}

	/*
		At this point we are guaranteed to have r <= 0.
			r == 0 means EOF (normal termination), and
			r < 0 means there was a read error.
	*/
	return r;

}

int
mainprog(int my_argc, char **my_argv)
{

	int k, fd, ret;

	/* All cases must end with program termination */
	if (my_argc > 1) {		/* Files specified, cat each of them */
		for (k=1; k < my_argc; k++) {
			if ((fd = os_open(my_argv[k], O_RDONLY, 0)) < 0) {
				my_fprintf(2, "open %s : %s", my_argv[k], openerr);
				os_exit(-fd);
			}
			ret = fdcat(fd, 1);
			if (ret < 0)       /* Got read error on this file, abort */
				break;
			os_close(fd);
		}
		terminate(ret);
	} else {				/* No files specified, cat std input (set fd = 0) */
		fd = 0;
		ret = fdcat(fd, 1);
		terminate(ret);
	}

	return 0;
}

