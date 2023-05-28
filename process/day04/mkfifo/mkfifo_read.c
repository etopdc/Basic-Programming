#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PATHNAME "./fifo_test"
int main(void)
{
    
    int fd = open(PATHNAME,O_RDONLY);
    if(fd==-1)
    {
        perror("[ERROR] open(): ");
        exit(EXIT_FAILURE);
    }
    ssize_t rbyte = 0;
    char buffer[64] = {0};
    rbyte = read(fd, buffer,sizeof(buffer));
    if(rbyte==-1)
    {
        perror("[ERROR] read():");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Read processs <%d> : %s",getpid(),buffer);
    close(fd);
    return 0;
}