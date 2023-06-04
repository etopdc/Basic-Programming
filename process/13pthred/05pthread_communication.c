/*
    进程间通信
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//线程执行函数
void *do_pthread(void *args)
{
    static int number = 100;// 设置static变量，防止栈区变量被释放
    pthread_exit(&number); //线程退出
}
int main(void)
{
    pthread_t ptid;
    int err;
    void *retval;

    err = pthread_create(&ptid, NULL, do_pthread, NULL);
    if(err!=0)
    {
        fprintf(stderr,"[ERROR] pthread_create(): %s\n",strerror(err));
        exit(EXIT_FAILURE);
    }
    printf("ptid = %ld\n",ptid);
    pthread_join(ptid,&retval);//等待子线程退出，这里会阻塞主线程
    printf("retval: %d\n",*(int *)retval);
    return 0;
}