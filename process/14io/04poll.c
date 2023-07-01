#include <stdio.h>
#include <sys/select.h>
#include <stdlib.h>
#include <poll.h>

int main(void)
{
    int ret;
    struct pollfd pollfds[1]={
        {0,POLLIN}//
    };

    for(;;)
    {
        int to = 3000;//timeval
        ret = poll(pollfds, 1, to);//(struct pollfd, number of poofds, timeval)
        if(ret==-1)
        {
            perror("[ERROR] poll(): \n");
            exit(EXIT_FAILURE);
        }
        else if(ret==0)//超时返回
        {
            printf("Timeout\n");
        }
        else if(ret>0)//有文件描述符就绪
        {
            char buffer[32]={0};
            fgets(buffer, sizeof(buffer), stdin);
            printf("buffer=%s\n",buffer);
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}