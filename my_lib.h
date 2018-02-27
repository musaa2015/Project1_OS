/*

File my_lib.h

User library functions (like the C library)

*/

int my_strcmp(char *ptr, char *ref);
void my_fprintf (int fd, const char *format, ...);
char **tokenize(char line);
