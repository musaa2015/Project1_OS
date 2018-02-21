/*

File os_syscalls.h

Standalone C system call wrappers for linux/i386.

*/

int os_read(unsigned int fd, char *buf, unsigned int len);
int os_write(unsigned int fd, char *buf, unsigned int len);
int os_exit(int exitcode);
int os_close(int fd);
int os_open(char *pathname, int flags, int mode);
int os_execve(const char *filename, char *const argv[], char *const envp[]);
int os_chdir(const char *path);
pid_t os_fork(void);
pid_t os_waitpid(pid_t pid, int *wstatus, int options);
