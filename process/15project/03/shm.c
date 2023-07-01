#include "shm.h"

#define PATHNAME "."
#define PROJ_ID 101//小于8位的数
enum shm_create_status shm_create(size_t size, int *shmid)
{
    int rshmid;
    key_t key;

    key=ftok(PATHNAME,PROJ_ID);
    rshmid=shmget(key, size, 0);//shmflg=0代表获取共享内存id
    if(rshmid==-1)//共享内存不存在
    {
        //fprintf(stdout,"share moment is not exist")
        rshmid = shmget(key,size,IPC_CREAT|0644);
        fprintf(stdout,"share moment id = %d\n",rshmid);
        if(rshmid==-1)
        {
            perror("[ERROR] shmget(): \n");
            return SHM_CREATE_ERR;
        }
        *shmid=rshmid;
        return SHM_CREATE_NEW;
    }
    else
    {
        *shmid=rshmid;
        return SHM_IS_EXITS;
    }
}

void *shm_at(int shmid)
{
    void *addr=NULL;
    addr=shmat(shmid,NULL,0);
    if(addr==(void *)-1)
    {
        perror("[ERROR] shmat(): ");
    }
    return addr;
}

int shm_dt(void *addr)
{
    return shmdt(addr);
}

int shm_del(int shmid)
{
    return shmctl(shmid,IPC_RMID,NULL);
}