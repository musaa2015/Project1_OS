/*

pipetwolines.c 

*/

#include "os_syscalls.h"
#include "my_lib.h"

#define MAXARGS 1024
#define MAXLEN 4096
char bufprognames[MAXLEN];

extern char *tokenList[];
int tokenize(char *);

int
mainprog(void)
{
	int k, r, ret, fd[2], status, pidA, pidB;
	char *progA, *progB, *envlist[1];


	my_fprintf(1, "Enter the full path to the writer program followed by arguments:\n");
	if ((r = os_read(0, bufprognames, MAXLEN)) <= 0)
		os_exit(-r);
	if (bufprognames[r - 1] != '\n') {
		my_fprintf(1, "Line buffer overflow\n");
		os_exit(-1);
	}
	bufprognames[r-1] = '\0';
	progA = bufprognames;
	k = r;

	my_fprintf(1, "Enter the full path to the reader program followed by arguments:\n");
	if ((r = os_read(0, bufprognames + k, MAXLEN - k)) <= 0)
		os_exit(-r);
	if (bufprognames[k + r - 1] != '\n') {
		my_fprintf(1, "Line buffer overflow\n");
		os_exit(-1);
	}
	bufprognames[k + r - 1] = '\0';
	progB = bufprognames + k;

	/* Set up array of env string ptrs --- no environment string! */
	envlist[0] = (char *)0;

	/* Create the pipe */
	if ((ret = os_pipe(fd)) < 0)
		os_exit(-ret);

	/* All ready now for main action! */

	if((r = tokenize(progB)) <0){
		my_fprintf(1, "Error tokenizing arguments for writer!\n");
	os_exit(-1);
	}
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
		os_execve(progB, tokenList, envlist); 
		/* Won't return if successful */
		my_fprintf(1, "Error:  execve(\"%s\") failed!\n", progB);
		os_exit(-1); 
		/* Child doesn't execute code outside this block */
	}

	/* In the parent again */

	
	if((r = tokenize(progA)) <0){
		my_fprintf(1, "Error tokenizing arguments for writer!\n");
		os_exit(-1);
	}


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
		os_execve(progA, tokenList, envlist);
		my_fprintf(1, "Error:  execve(\"%s\") failed!\n", progA);
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
