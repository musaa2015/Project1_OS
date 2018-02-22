/*

File os_syscalls.h

Standalone C system call wrappers for linux/i386.

*/

int os_read(unsigned int fd, char *buf, unsigned int len);
int os_write(unsigned int fd, char *buf, unsigned int len);
int os_exit(int exitcode);
int os_close(int fd);
int os_open(char *pathname, int flags, int mode);
int os_execve(char *filename, char *argv[], char *envp[]);
int os_fork(void);
int os_waitpid(int pid, int *wstatus, int options);
