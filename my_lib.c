/*

File my_lib.c

User library functions (like the C library functions, cf. man 3)

Each non-static global function name is prefixed with "my_".

Some of these are adapted from the file kernel.c found in
GNU Multiboot Specification documents, version 0.6.96.

A copy of the GPL3 (Gnu Public License v3) copyright notice
is given below.

*/

/* kernel.c - the C part of the kernel */
/* Copyright (C) 1999, 2010  Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "os_syscalls.h"

int
my_strcmp(char *ptr, char *ref)
{
	while (1) {
		if (*ptr == '\0' || *ref == '\0')
			break;
		if (*ptr != *ref)
			break;
		ptr++; ref++;
	}
	return (int)(*ptr - *ref);
}

/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal. */
static void
itoa (char *buf, int base, long d)
{
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	long divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x')
		divisor = 16;

	/* Divide UD by DIVISOR until UD == 0. */
	do {
		long remainder = ud % divisor;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);

	/* Terminate BUF. */
	*p = 0;

	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

/* Write one character --- no buffering --- for testing only */
/*
static void
fdputchar_nobuf (int fd, char c, int flushonly)
{
	os_write(fd, &c, 1);
}
*/

#define BUFSIZE  256
#define MAXFD 256

/* Write one character --- with buffering!!! */
static int
fdputchar (int fd, char c, int flushonly /* if == 1 just flush buffer */)
{

	int n,j,w;
	char outbuf[BUFSIZE];

	static char infifo[MAXFD][BUFSIZE];  /* ring fifo of size BUFSIZE-1 */
	static int pstart[MAXFD], pend[MAXFD];

	if (fd < 0 || fd >= MAXFD)
		return -1;

	/*	Each fifo ring buffer here is implemented by an array of
		size BUFSIZE and two pointers to it, pstart and pend,
		with pstart pointing to the first byte, and pend-1
		pointing to the last byte.  The byte pointed to by pend
		is invalid, so the buffer can hold at most BUFSIZE-1 bytes.
			0 <= pstart, pend < BUFSIZE
			The buffer contents are at indices
				pstart, pstart+1, ..., pend-1 (mod BUFSIZE) 
			Buffer is empty iff pend == pstart
			Buffer is full iff pend + 1 == pstart mod BUFSIZE
			The buffer size is:  pend - pstart if pstart <= pend,
			else pend + BUFSIZE - pstart
	*/

	/* Compute buffer size */
	/* Be Careful with signed integer modulo a smaller modulus! */
	n = (pend[fd] + (BUFSIZE - pstart[fd]))%BUFSIZE;

	/* Two other ways to compute the buffer size and put in n:

	for (n = 0; ((pstart[fd] + n)%BUFSIZE) != pend[fd]; n++)
		;

	if (pstart[fd] <= pend[fd])
		n = pend[fd] - pstart[fd];
	else
		n = (pend[fd] + BUFSIZE) - pstart[fd];

	*/

	if (n == BUFSIZE-1 || (n > 0 && flushonly == 1)) {
		/* infifo full or flush requested, try writing */
		for (j = 0; j < n; j++)
			outbuf[j] = infifo[fd][(pstart[fd] + j)%BUFSIZE];
		w = os_write(fd, outbuf, n);
		if (w != n) /* write error */ {
			// os_write(2, "write() err\n", sizeof("write() err\n")-1);
			return -2;
		}
		pstart[fd] = (pstart[fd] + w)%BUFSIZE;
	}
	if (flushonly == 1) /* Ignore character c if flushonly==1 */
		return 0;
	/* We now have room in buffer, so put the char in it */
	infifo[fd][pend[fd]] = c;
	pend[fd] = (pend[fd] + 1)%BUFSIZE;
	return 0;

}

/* Format a string and print it on the screen, just like the libc
   function printf. */
void
my_fprintf (int fd, const char *format, ...)
{
	char **arg = (char **) &format;
	char c;
	char buf[40];

	arg++; /* Doesn't work in 64bit ABI */

	while ((c = *format++) != 0) {
		if (c != '%')
			fdputchar(fd, c, 0);
		else {
			char *p, *p2;
			int pad0 = 0, pad = 0;

			c = *format++;

			if (c == '%') {
				fdputchar(fd, c, 0);
				continue;
			}

			if (c == '0') {
				pad0 = 1;
				c = *format++;
			}

			while (c >= '0' && c <= '9') {
				pad = 10*pad + c - '0';
				c = *format++;
			}

			switch (c) {
				case '\0':  /* Premature end of format str, abort */
					format--;  /* Now we have *format == '\0' */
					break;

				case 'd':
				case 'u':
				case 'x':
					itoa (buf, c, *((long *) arg++));
					p = buf;
					goto string;
					break;

				case 's':
					p = *arg++;
					if (! p)
						p = "(null)";

				string:
					for (p2 = p; *p2; p2++);
					c = (pad0 ? '0' : ' ');
					for (; p2 < p + pad; p2++)
						fdputchar(fd, c, 0);
					while (*p)
						fdputchar(fd, *(p++), 0);
					break;

				default: /* Invalid format specifier charcter after '%' */
					itoa (buf, 'x', (long) arg++);
					p = buf;
					fdputchar(fd, '[', 0);
					fdputchar(fd, 'x', 0);
					while (*p)
						fdputchar(fd, *(p++), 0);
					fdputchar(fd, ']', 0);
					break;
			}
		}
	}
	fdputchar(fd, 0, 1); /* flush */
}

**char
tokenize(char line)
{
		int tokenCount=0, character=0, i=0;
		**char tokens;
		
		while(line[character] != '\0'){
			for(int i = 0; line[character] != " "; i++){
				tokens[tokenCount][i] = line[character];
				character++;
			}
			if(line[i] == " "){
				tokens[tokenCount][i] = '\0';
				tokenCount++;
				character++;
			}
		}
		
		return tokens;
}
