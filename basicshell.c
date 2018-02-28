/*

basicshell.c

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

  gcc -m32 -Wall -nostdlib -o basicshell basicshell.c startup32.S os_syscalls.c my_lib.c

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
	int r, pid, status;
	//char *pwd[1] = {"/bin/pwd"};

	while (1==1){

		//Print CWD after each command. 
		/*pid = os_fork();
		if (pid < 0)
			os_exit(-pid);
		if (pid == 0){
			os_execve(*pwd, pwd, '\0');
			os_exit(-1);
		}
		os_waitpid(pid, &status, 0);*/	
		//Removed it because it not printing on the same line as the "$".	
	
		my_fprintf(1,"$ ");
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

		pid = os_fork();
		if (pid < 0)
			os_exit(-pid);

		if (pid == 0 && !(my_strcmp(tokenList[0], "cd") == 0)) {	
			os_execve(prog, tokenList, envlist);
			my_fprintf(1, "Error:  execve(\"%s\") failed!\n", prog);
			os_exit(-1);  
		}
		else if((my_strcmp(tokenList[0], "cd") == 0) && (r = os_chdir(tokenList[1])) != 0){
			my_fprintf(1, "Error:  Could not cd to \"%s\"!\n", tokenList[1]);
		}
		
		os_waitpid(pid, &status, 0);
	}
	return 0;
}
