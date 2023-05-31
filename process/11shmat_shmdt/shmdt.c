#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

/*
    将物理地址中上的共享内存映射到进程的地址空间
*/
#define PATHNAME "."
#define PRO_ID 88
#define SHM_SZ 256
int main(void)
{
    key_t key;
    key = ftok(PATHNAME,PRO_ID);    //获取唯一标识符
    if(key==-1)
    {
        perror("[ERROR] ftok(): ");
        exit(EXIT_FAILURE);
    }
    int shmid;
    shmid = shmget(key, SHM_SZ, IPC_CREAT|0644);    //调用共享内存
    if(shmid==-1)
    {
        perror("[ERROR] shmget(): ");
        exit(EXIT_FAILURE);
    }
    printf("shmid : %d",shmid);
    void *shmaddr;  //映射空间地址
    shmaddr = shmat(shmid,NULL,0); //第二个参数shmaddr设置为NULL，系统会自动在地址空间选择映射的起始地址
    if(shmaddr==(void *)-1)
    {
        perror("[ERROR] shmat(): ");
        exit(EXIT_FAILURE);
    }

    char shmbuffer[20] = {0};
    memcpy(shmbuffer,shmaddr,16);
    printf("shmbuffer:%s",shmbuffer);

    shmdt(shmaddr);//解除映射
    return 0;
}