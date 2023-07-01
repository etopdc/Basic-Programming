/*
    线程互斥锁
    使用互斥锁的情况
    pthread_mutex_lock
    pthread_mutex_unlock
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static int global = 0;//临界资源
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;//线程互斥锁
void *do_pthread(void *arg)
{
    int loops = *(int *)arg;
    int temp = 0;
    for(int i=0;i<loops;i++)
    {
        pthread_mutex_lock(&mtx);//加锁
        temp = global;
        temp++;
        global = temp;
        pthread_mutex_unlock(&mtx);//解锁
    }
    pthread_exit(NULL);//线程退出
}

int main(int args, char *argv[])
{
    int err;
    int loops;
    pthread_t ptid[2]={0};


    if(args!=2)
    {
        fprintf(stderr,"Usage:  <%s>",argv[0]);
        exit(EXIT_FAILURE);
    }

    loops = atoi(argv[1]);

    for(int i=0;i<2;i++)
    {
        //创建线程
        err = pthread_create(&ptid[i], NULL, do_pthread, (void *)&loops);
    }

    pthread_join(ptid[0], NULL);//等待线程
    pthread_join(ptid[1], NULL);

    printf("%d\n",global);
    
    return 0;
}