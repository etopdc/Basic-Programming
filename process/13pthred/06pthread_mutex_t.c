/*
    线程互斥锁
    不适用互斥锁的情况
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static int global = 0;
void *do_pthread(void *arg)
{
    int loops = *(int *)arg;
    int temp = 0;
    for(int i=0;i<loops;i++)
    {
        temp = global;
        temp++;
        global = temp;
    }
    pthread_exit(NULL);
}

int main(int args, char *argv[])
{
    int err;
    int loops;//循环次数
    pthread_t ptid[2]={0};//线程id

    if(args!=2)
    {
        fprintf(stderr,"Usage:  <%s>",argv[0]);
        exit(EXIT_FAILURE);
    }

    loops = atoi(argv[1]);//转换为整型

    for(int i=0;i<2;i++)
    {
        //创建进程
        err = pthread_create(&ptid[i], NULL, do_pthread, (void *)&loops);
    }

    pthread_join(ptid[0], NULL);//进程等待
    pthread_join(ptid[1], NULL);

    printf("%d\n",global);
    
    return 0;
}