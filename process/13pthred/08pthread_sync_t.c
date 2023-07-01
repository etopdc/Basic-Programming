/*
    使用互斥锁进行线程同步
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static int global = 0;//临界资源
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;//线程互斥锁
void *do_pthread(void *arg)
{
    int loops = atoi((char *)arg);
    for(int i=0;i<loops;i++)
    {
        pthread_mutex_lock(&mtx);//加锁
        printf("线程[%ld]生产一个产品，当前产品数：%d\n",pthread_self(),++global);
        pthread_mutex_unlock(&mtx);//解锁
    }
    pthread_exit(NULL);//线程退出
}

int main(int args, char *argv[])
{
    int err;
    int loops;
    pthread_t ptid[args-1];
    memset(ptid,0,sizeof(ptid)/sizeof(ptid[0]));
    int total_consume = 0;
    int total_produce = 0;


    if(args<2)
    {
        fprintf(stderr,"Usage:  <%s>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<args;i++)
    {
        total_produce += atoi(argv[i]);
        //创建线程
        err = pthread_create(&ptid[i], NULL, do_pthread, (void *)argv[i]);
    }

    for(;;)
    {
        while(global>0)
        {
            pthread_mutex_lock(&mtx);
            printf("消费一个产品，当前产品总数：%d\n",--global);
            total_consume +=1;
            pthread_mutex_unlock(&mtx);
        }
        if(total_consume>=total_produce)
        {
            break;
        }
    }

    return 0;
}