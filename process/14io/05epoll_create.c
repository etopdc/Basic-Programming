#include <stdio.h>
#include <sys/epoll.h>

int main(void)
{
    int epfd;
    epfd=epoll_create(10);//创建epoll实例
    if(epfd==-1)
    {
        perror("[ERROR] epoll_create(): ");
    }
    printf("%d\n",epfd);
    return 0;
}