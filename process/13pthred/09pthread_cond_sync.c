/*
    线程同步（在互斥的基础上增加对资源访问顺序的控制）
    while(global>0)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static int global = 0;//临界资源
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;//线程互斥锁
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;//信号变量静态初始化
void *do_pthread(void *arg)
{
    int loops = atoi((char *)arg);
    for(int i=0;i<loops;i++)
    {
        pthread_mutex_lock(&mtx);//加锁
        printf("线程[%ld]生产一个产品，当前产品数：%d\n",pthread_self(),++global);
        pthread_mutex_unlock(&mtx);//解锁
        pthread_cond_signal(&cond);//唤醒信号
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
        pthread_mutex_lock(&mtx);
        //为什么用while，不用if
        //防止虚假唤醒
        while(global==0)//仓库中没有产品，等待
        {
            pthread_cond_wait(&cond, &mtx);//1、解锁 2.让线程阻塞在条件变量上 3.当信号变量收到唤醒信号后，线程唤醒，重新竞争锁
        }

        printf("消费一个产品，当前产品总数：%d\n",--global);
        total_consume +=1;
        pthread_mutex_unlock(&mtx);//解锁

        if(total_consume>=total_produce)
        {
            break;
        }
    }

    return 0;
}