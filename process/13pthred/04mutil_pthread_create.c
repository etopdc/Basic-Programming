/*
    创建多个线程
    多线程做相同的事情
    多线程做不同的事情
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *do_pthread_A(void *args)
{
    printf("do pthread A!\n");
    pthread_exit(NULL);
}
void *do_pthread_B(void *args)
{
    printf("do pthread B!\n");
    pthread_exit(NULL);
}

int main(void)
{
#if 0
    pthread_t ptid_A,ptid_B;
    int err;

    err = pthread_create(&ptid_A, NULL, do_pthread_A, NULL);
    if(err!=0)
    {
        fprintf(stderr,"[ERROR] pthread_create(): %s\n",strerror(err));
        exit(EXIT_FAILURE);
    }
    err = pthread_create(&ptid_B, NULL, do_pthread_B, NULL);
    if(err!=0)
    {
        fprintf(stderr,"[ERROR] pthread_create(): %s\n",strerror(err));
        exit(EXIT_FAILURE);
    }
    printf("ptid_A = %ld\n",ptid_A);
    printf("ptid_B = %ld\n",ptid_B);
    pthread_join(ptid_A,NULL);//等待子线程退出，这里会阻塞主线程
    pthread_join(ptid_B,NULL);//等待子线程退出，这里会阻塞主线程
#endif
    pthread_t ptid[2]={0};
    int err;
    for(int i=0;i<2;i++)
    {
        err = pthread_create(&ptid[i], NULL, do_pthread_A, NULL);
        if(err!=0)
        {
            fprintf(stderr,"[ERROR] pthread_create(): %s\n",strerror(err));
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}