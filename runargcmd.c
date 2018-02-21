
#include "os_syscalls.h"
#include "my_lib.h"

#define MAXLEN 256
char buf[MAXLEN];

int mainprog(void)
{
	int r, pid, status;
	char *arglist[2], *evlist[2];
	envlist[0] = (char *)0;

	while((r=read(0,buf, MAXLEN)) > 0){
	
		write(1,">",1);
		buf[r-1] = '\0';

		pid = os_fork()

	}
}
