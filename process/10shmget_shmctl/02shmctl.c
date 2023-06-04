#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

/*
    创建共享内存后，删除
*/

//ipcid
#define PATHNAME "."
#define PRO_ID 102

//she
#define SHM_SZ 256
int main()
{
    int shmid,ret;
    key_t key;
    key = ftok(PATHNAME,PRO_ID);
    if(key==-1)
    {

    }

    //创建共享内存
    shmid = shmget(key, SHM_SZ, IPC_CREAT|0644);
    if(shmid==-1)
    {

    }
    fprintf(stdout,"shmid: %d\n",shmid);
    ret = shmctl(shmid, IPC_RMID, NULL);
    if(ret==-1)
    {
        perror("[ERROR] shectl(): ");
        exit(EXIT_FAILURE);
    }
    return 0;
}