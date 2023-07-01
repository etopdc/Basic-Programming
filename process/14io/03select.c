#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>

int main(void)
{
    int ret;
    int maxfd = 0;
    fd_set readfds;
    fd_set readfds_tmp;
    FD_ZERO(&readfds);//将文件描述符集合清空
    FD_ZERO(&readfds_tmp);
    FD_SET(0,&readfds);//将文件描述符添加到文件描述符集合中
    struct timeval tv;
    struct timeval tv_tmp={3,0};

    /*
        1.3s之后，没有文件描述符就绪，就会超时返回0
        2.timeval的值是会被select修改的，用过一次以后，就会被重新赋值为0
        3.select会将就绪的文件描述符直接拷贝覆盖到原集合中，
          变相的相当于把没有就绪的文件描述符给直接删除了，如果是超时返回的话，
          会直接清空文件描述符集合
    */

    for(;;)
    {
        tv =tv_tmp;
        readfds_tmp = readfds;
        ret = select(maxfd+1, &readfds_tmp,NULL,NULL,&tv);
        if(ret==-1)
        {
            perror("[ERROR] select(): \n");
            exit(EXIT_FAILURE);
        }
        else if(ret==0)//超时返回
        {
            printf("Timeout\n");
        }
        else if(ret>0)//有文件描述符就绪
        {
            if(FD_ISSET(0,&readfds_tmp))//判断是否是标准输入的文件描述符就绪
            {
                char buffer[32]={0};
                //stdin 是FILE *文件指针
                //0 是int 文件描述符
                fgets(buffer, sizeof(buffer), stdin);
                printf("buffer=%s\n",buffer);
                exit(EXIT_SUCCESS);
            }
        }
    }
    return 0;
}