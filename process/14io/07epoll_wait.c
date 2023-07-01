#include <stdio.h>
#include <sys/epoll.h>
#include <stdlib.h>

#define MAXEVENTS 10

int main(void)
{
    int epfd;
    int ret;
    struct epoll_event ev;//定义事件结构体（关联文件描述符和对应的监控的事件）

    ev.events = EPOLLIN;
    ev.data.fd = 0;

    epfd=epoll_create(10);//创建epoll实例
    if(epfd==-1)
    {
        perror("[ERROR] epoll_create(): \n");
        exit(EXIT_FAILURE);
    }
    printf("%d\n",epfd);

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, 0,&ev);//将标准文件描述符添加到epoll实例
    if(epfd==-1)
    {
        perror("[ERROR] epoll_create(): \n");
        exit(EXIT_FAILURE);
    }

    struct epoll_event events[MAXEVENTS];
    int ret_wait;
    char buffer[32]={0};
    for(;;){
        ret_wait = epoll_wait(epfd, events,MAXEVENTS,1000);//等待文件描述符关联的事件发生
        if(ret_wait==-1)
        {
            perror("[ERROR] epoll_wait(): \n");
            exit(EXIT_FAILURE);
        }
        else if(ret_wait==0)//超时
        {
            printf("Timeout\n");
        }
        else if(ret_wait>0)//返回就绪文件描述符个数
        {
            for(int i=0;i<ret_wait;i++)
            {
                if(events[i].data.fd==0)//是标志输入文件描述符
                {
                    fgets(buffer,sizeof(buffer),stdin);
                    printf("buffer=%s\n",buffer);
                }
            }

        }
    }
   


    return 0;
}