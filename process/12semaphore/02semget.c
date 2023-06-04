#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEM_SET_PATHNAME "."
#define SEM_SET_PRO_ID 88
#define SEM_SET_SZ 1

int main(void)
{
    //创建IPC标识符
    key_t key;
    key = ftok(SEM_SET_PATHNAME,SEM_SET_PRO_ID);
    if(key==-1)
    {
        perror("[ERROR] ftok(): ");
        exit(EXIT_FAILURE);
    }

    //创建信号量集合
    int semid;
    semid = semget(key, SEM_SET_SZ, IPC_CREAT|0644);
    if(semid==-1){}
    printf("semid:%d",semid);

    return 0;
}