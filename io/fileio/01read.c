#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int fd;
    ssize_t rstate = 0;
	ssize_t wstate = 0;
	char buffer[64] = {0};
	char wbuffer[] = "ABCDE12345";

    if(argc !=2)
    {
        fprintf(stderr, "Usage : %s pathnames",argv[0]);
        return -1;
    }
    
    fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0777); //读写、创建、清空
    if(fd==-1)
    {
        perror("open():");
        return -1;
    }
    printf("fd:%d\n",fd);
    rstate =  write(fd,wbuffer, strlen(wbuffer));
    if(rstate==-1)
    {
        perror("write():");
        return -1;
    }

    lseek(fd,0,SEEK_SET);
    char aaa[64]={0};
    wstate = read(fd, aaa, strlen(wbuffer));
    if(wstate==-1)
    {
        perror("read():");
        return -1;
    }
    printf("read file : %s\n",aaa);

    close(fd);
    return 0;
}