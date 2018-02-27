#include "os_syscalls.h"
#include "my_lib.h"

int mainprog(int argc, char **argv,char **envp)
  {
  int r;
  char input[4096];
  int tf = 1;
  int test;
  my_fprintf(1,"%s ","Enter the environment variable you want to view\n");
  if ((r = os_read(0,input,4096)) <= 0)
    os_exit(-r);
//  os_write();
  //my_fscanf("%s", &input);
  char **env;
  for(env = envp; *env != 0; env++){
    char *thisEnv = *env;
    test = my_strcmp(input, thisEnv);
    if (test) {
      my_fprintf(1,"%s ", thisEnv);
      tf = 0;
      }
    }
  if (tf) {
  my_fprintf(1,"%s ","Could not find Environment variable for user input\n");
  }
  return 0;
  }
