/*

pipetwolines.c


  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);


  gcc -m32 -Wall -nostdlib -o pipetwolines pipetwolines.c startup32.S os_syscalls.c my_lib.c


*/

#include "os_syscalls.h"
#include "my_lib.h"


#define MAXLEN 4096
char bufprognames[MAXLEN];
char tmpbuf[MAXLEN];

int
mainprog(void)
{
	int k, r, ret, fd[2], status, pidA, pidB;
	char *progA, *progB, *arglistA[2], *arglistB[2], *envlist[1];


	my_fprintf(2, "Enter the name of the writer program:\n");
	if ((r = os_read(0, bufprognames, MAXLEN)) <= 0)
		os_exit(-r);
	if (bufprognames[r - 1] != '\n') {
		my_fprintf(2, "Line buffer overflow\n");
		os_exit(-1);
	}
	bufprognames[r-1] = '\0';
	progA = bufprognames;
	k = r;

	my_fprintf(2, "Enter the name of the reader program:\n");
	if ((r = os_read(0, bufprognames + k, MAXLEN - k)) <= 0)
		os_exit(-r);
	if (bufprognames[k + r - 1] != '\n') {
		my_fprintf(2, "Line buffer overflow\n");
		os_exit(-1);
	}
	bufprognames[k + r - 1] = '\0';
	progB = bufprognames + k;


	envlist[0] = (char *)0;

		os_exit(-ret);


	pidB = os_fork();
	if (pidB < 0)
		os_exit(-pidB);

	if (pidB == 0) {	
		os_close(fd[1]);
		if (fd[0] != 0){
			os_dup2(fd[0], 0);
			os_close(fd[0]);
		}
		os_execve(progB, progB, envlist);
		my_fprintf(2, "Error:  execve(\"%s\") failed!\n", progB);
		os_exit(-1);
	}

	pidA = os_fork();
	if (pidA < 0)
		os_exit(-pidA);

	if (pidA == 0) {
		os_close(fd[0]);
		if (fd[1] != 1) {
			os_dup2(fd[1], 1);
			os_close(fd[1]);
		}
		os_execve(progA, progA, envlist);
		my_fprintf(2, "Error:  execve(\"%s\") failed!\n", progA);
		os_exit(-1); 
	}
	os_close(fd[0]);
	os_close(fd[1]);
	os_waitpid(pidB, &status, 0);
	os_waitpid(pidA, &status, 0);

	return 0;
}

