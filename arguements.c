#include <stdio.h>

void main(int argc, char *argv[])
{
int a;
for(a = 0;a < argc;a++)
  {
  printf("%s ", argv[a]);
  }
  printf("\n");
}
