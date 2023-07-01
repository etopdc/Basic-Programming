#include "thread_pool.h"

void pthread_task(void *arg)
{
    int *p = (int *)arg;
    printf("task thread %ld is working ,number=%d\n",pthread_self(),*p);
}

int main()
{
    tpool_t *tpool = thread_pool_init(20,100);
    int *p =NULL;
    for(int i=0;i<100;i++)
    {
        p=(int *)malloc(sizeof(int));
        *p = i+100; 
        thread_pool_add_task(tpool,pthread_task,(void *)p);
    }
    while(1)
    {

    }
    return 0;
}
