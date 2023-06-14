#include "sem.h"


union semun{
    unsigned short *array;
};

/*
    @param  nsems:信号量的数量
    @param  array:信号量的值

    @return:
        success:信号量集合id
        fail:-1
*/
int create_sem(int nsems, unsigned short array[])
{
    key_t key;
    int semid;
    int ret;
    union semun s;


    key = ftok(SEM_SET_PATHNAME,SEM_SET_PRO_ID);
    if(key==-1)
    {
		perror("[ERROR] ftok() : ");
		return -1;
    }
    semid = semget(key,nsems,IPC_CREAT|0644);
    if(semid==-1)
    {
        perror("[ERROR] semget() : ");
		return -1;
    }
    printf("semid = %d\n",semid);
    s.array = array;
    ret = semctl(semid,0,SETALL,s);
    if(ret==-1)
    {
		perror("[ERROR] semctl() : ");
		return -1;
    }
    return semid;
}

/*
    @param  semid:信号量的id
    @param  semnum:操作的信号量的编号

    @return:
        success:0
        fail:-1
*/
int option_sem_occupy(int semid, unsigned short semnum)
{
    int ret;
    struct sembuf sops;

    sops.sem_num = semnum;
    sops.sem_op = -1;
    sops.sem_flg = SEM_UNDO;
    ret = semop(semid,&sops,1);
    return ret;
}
/*
    @param  semid:信号量的id
    @param  semnum:操作的信号量的编号

    @return:
        success:0
        fail:-1
*/
int option_sem_release(int semid, unsigned short semnum)
{
    int ret;
    struct sembuf sops;

    sops.sem_num = semnum;
    sops.sem_op = 1;
    sops.sem_flg = SEM_UNDO;
    ret = semop(semid,&sops,1);
    return ret;
}

/*
    @param  semid:信号量的id

    @return​
        success:0
        fail:-1
*/
int del_sem(int semid)
{
    return semctl(semid,0,IPC_RMID,NULL);
}