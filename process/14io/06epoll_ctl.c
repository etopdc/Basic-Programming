#include <stdio.h>
#include <sys/epoll.h>
#include <stdlib.h>

int main(void)
{
    int epfd;
    int ret;
    struct epoll_event ev;//定义事件结构体（关联文件描述符和对应的监控的事件）

    ev.envents = EPOLLIN;
    ev.data.fd = 0;

    epfd=epoll_create(10);//创建epoll实例
    if(epfd==-1)
    {
        perror("[ERROR] epoll_create(): ");
        exit(EXIT_FAILURE);
    }
    printf("%d\n",epfd);

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, &ev);//将标准文件描述符添加到epoll实例
    if(epfd==-1)
    {
        perror("[ERROR] epoll_create(): ");
        exit(EXIT_FAILURE);
    }
    return 0;
}