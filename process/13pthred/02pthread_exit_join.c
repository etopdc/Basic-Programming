/*
    进程的退出和等待
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//线程执行函数
void *do_pthread(void *args)
{
    printf("do pthread!\n");
    pthread_exit(NULL); //线程退出
}
int main(void)
{
    pthread_t ptid;
    int err;

    err = pthread_create(&ptid, NULL, do_pthread, NULL);
    if(err!=0)
    {
        fprintf(stderr,"[ERROR] pthread_create(): %s\n",strerror(err));
        exit(EXIT_FAILURE);
    }
    printf("ptid = %ld\n",ptid);
    pthread_join(ptid,NULL);//等待子线程退出，这里会阻塞主线程
    return 0;
}