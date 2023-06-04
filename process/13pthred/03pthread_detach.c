/*
    进程的分离
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

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
    //pthread_join(ptid,NULL);//等待子线程退出，这里会阻塞主线程
    pthread_detach(ptid);//进行线程分离，由操作系统自动自动释放子线程的资源，不会阻塞主线程
    #if 0
    while(1)
    {

    }
    #endif
    return 0;
}