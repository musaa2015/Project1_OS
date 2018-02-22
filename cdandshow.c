/*

cdandshow.c

  int mainprog(void);
  int mainprog(int argc);
  int mainprog(int argc, char **argv);
  int mainprog(int argc, char **argv, char **envp);

Or as one command (not equivalent):

	gcc -m32 -Wall -nostdlib -o cdandshow cdandshow.c startup32.S os_syscalls.c my_lib.c

*/

#include "os_syscalls.h"
#include "my_lib.h"

int mainprog(int argc, char **argv)
{
	char *pwd[1] = {"/bin/pwd"};
	int r;	
	
	if((r = os_chdir(*(argv+1))) == 0){
		os_write(1,"Success! New CWD: ",18);
		os_execve(*pwd, pwd, '\0');
	}
	else{
		my_fprintf(1,"Error: could not cd to %s.\n",*(argv+1));
	}
	return 0;
}
