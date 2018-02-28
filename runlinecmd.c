/*

runlinecmd.c

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

  gcc -m32 -Wall -nostdlib -o runlinecmd runlinecmd.c startup32.S os_syscalls.c my_lib.c

*/

#include "os_syscalls.h"
#include "my_lib.h"

#define MAXLEN 4096
char buf[MAXLEN];

extern char *tokenList[];
int tokenize(char *);

int mainprog(void)
{
	char *prog;
	char *envlist[1] = {(char *)0};
	int r;
	
	my_fprintf(1,"Enter CMD > ");
	if ((r = os_read(0, buf, MAXLEN)) <= 0)
		os_exit(-r);
	if (buf[r-1] != '\n'){
		my_fprintf(1, "Line buffer overflow.\n");
		os_exit(-1);	
	}
	buf[r-1] = '\0';
	prog = buf;	

	if((r = tokenize(prog)) <0){
		my_fprintf(1, "Error tokenizing arguments for writer!\n");
		os_exit(-1);
	}

	os_execve(prog, tokenList, envlist);
	my_fprintf(1, "Error:  execve(\"%s\") failed!\n", prog);
	os_exit(-1); 
	
	return 0;
}
