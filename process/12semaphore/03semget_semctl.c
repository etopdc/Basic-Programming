#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEM_SET_PATHNAME "."
#define SEM_SET_PRO_ID 88
#define SEM_SET_SZ 1

//信号量赋值共用体
union semun{
    int val;
};
int main(void)
{
    //创建IPC唯一标识符
    key_t key;
    key = ftok(SEM_SET_PATHNAME,SEM_SET_PRO_ID);
    if(key==-1)
    {
        perror("[ERROR] ftok(): \n");
        exit(EXIT_FAILURE);
    }

    //创建信号量集合
    int semid;
    semid = semget(key, SEM_SET_SZ, IPC_CREAT|0644);
    if(semid==-1){}
    printf("semid:%d\n",semid);

    //信号量集合初始化
    union semun s;
    s.val = 1;
    int ret;
    /*
        semctl()
        @params    semid，信号量起始编号,命令，值结构体指针 
    */
    ret = semctl(semid,0,SETVAL,s);  
    if(ret==-1)
    {
        perror("[ERROR] semctl(): \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}