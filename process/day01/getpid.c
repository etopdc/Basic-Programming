#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = 0;
    pid_t ppid = 0;
    pid = getpid();
    ppid = getppid();
    fprintf(stdout,"pid: %d  ppid: %d\n",pid,ppid);
    return 0;
}