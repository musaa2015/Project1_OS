#include "os_syscalls.h"
#include "my_lib.h"

int mainprog(int argc, char **argv)
{
	for(int a = 1; a < argc; a++){	
		my_fprintf(1,"%s ", argv[a]);
	}
	my_fprintf(1,"\n");

	return 0;
}
