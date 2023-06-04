/*
    创建多个进程
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *do_pthread(void *args)
{
    printf("do pthread!\n");
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
    return 0;
}