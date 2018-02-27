/*

pipetwolines.c :  Demo pipe program

- Reads commands from two separate lines
- Waits for user confirmation before and after pipe creation (for class demo)
- Does not do path searching --- full program pathnames need to be given
- Does not do tokenization --- programs cannot take any arguments

It would be instructive for the student to first try to remove the
last restriction, i.e. improve this code so that (i) each line is first
tokenized into separate null-terminated string tokens, (ii) an array
of string pointers is set up to point to these string tokens with
an extra null pointer added as the last element of the array, and
(iii) this array of string pointers is passed as the argv list
to the execve() function.  This way, the commands entered by the
user (on each line) can take arguments!

*/

#include "os_syscalls.h"
#include "my_lib.h"

#define MAXLEN 4096
char bufprognames[MAXLEN];

int
mainprog(void)
{
	int k, r, ret, fd[2], status, pidA, pidB;
	char *progA, *progB, *arglistA[2], *arglistB[2], *envlist[1];


	my_fprintf(2, "Enter the full path to the writer program:\n");
	if ((r = os_read(0, bufprognames, MAXLEN)) <= 0)
		os_exit(-r);
	if (bufprognames[r - 1] != '\n') {
		my_fprintf(2, "Line buffer overflow\n");
		os_exit(-1);
	}
	bufprognames[r-1] = '\0';
	progA = bufprognames;
	k = r;

	my_fprintf(2, "Enter the full path to the reader program:\n");
	if ((r = os_read(0, bufprognames + k, MAXLEN - k)) <= 0)
		os_exit(-r);
	if (bufprognames[k + r - 1] != '\n') {
		my_fprintf(2, "Line buffer overflow\n");
		os_exit(-1);
	}
	bufprognames[k + r - 1] = '\0';
	progB = bufprognames + k;


	/* Set up arrays of arg string ptrs --- no arguments for our programs! */
	arglistA[0] = progA;
	arglistA[1] = (char *)0;
	arglistB[0] = progB;
	arglistB[1] = (char *)0;

	/* Set up array of env string ptrs --- no environment string! */
	envlist[0] = (char *)0;

 
	/* Create the pipe */
	if ((ret = os_pipe(fd)) < 0)
		os_exit(-ret);


	/* All ready now for main action! */

	/* First, proceed to fork-exec the reader (progB) */
	pidB = os_fork();
	if (pidB < 0)
		os_exit(-pidB);

	/* Child to execve the reader program (progB) */
	if (pidB == 0) {	
		os_close(fd[1]);
		/* Reader won't need the write end */
		/* If the read end fd is already numbered 0 we can execve(progB) now,
		   else we will force it to become the number 0, using dup2() */
		if (fd[0] != 0) {
			os_dup2(fd[0], 0);
			os_close(fd[0]);
		}
		os_execve(progB, arglistB, envlist); 
		/* Won't return if successful */
		my_fprintf(2, "Err:  execve(\"%s\") failed!\n", progB);
		os_exit(-1); 
		/* Child doesn't execute code outside this block */
	}

	/* In the parent again */

	/* Next, proceed to fork-exec the writer (progA) */
	pidA = os_fork();
	if (pidA < 0)
		os_exit(-pidA);
	
	/* Child to execve the writer program (progA) */
	if (pidA == 0) {	
		/* Writer won't need the read end */
		os_close(fd[0]);
		/* If necessary, dup2() the write end fd to 1 */		
		if (fd[1] != 1) {	
			os_dup2(fd[1], 1);
			os_close(fd[1]);
		}
		os_execve(progA, arglistA, envlist);
		my_fprintf(2, "Err:  execve(\"%s\") failed!\n", progA);
		os_exit(-1); 
		/* Child doesn't execute code outside this block */
	}

	/* Clean up */
	os_close(fd[0]);
	os_close(fd[1]);
	os_waitpid(pidB, &status, 0);
	os_waitpid(pidA, &status, 0);

	return 0;
}
