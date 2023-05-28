#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PATHNAME "./fifo_test"
int main(void)
{
    int ret;
    // 创建管道
    ret = mkfifo(PATHNAME,0644);
    if(ret==-1)
    {
        perror("[ERROR] mkfifo(): ");
        exit(EXIT_FAILURE);
    }
    int fd = open(PATHNAME,O_WRONLY);
    if(fd==-1)
    {
        perror("[ERROR] open(): ");
        exit(EXIT_FAILURE);
    }
    ssize_t wbyte = 0;
    char buffer[] = "hello mkfifo";
    wbyte = write(fd, buffer,strlen(buffer));
    if(wbyte==-1)
    {
        perror("[ERROR] write():");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}