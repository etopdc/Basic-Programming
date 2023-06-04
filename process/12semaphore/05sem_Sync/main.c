/*
    同步：在互斥的基础上，增加进程访问顺序的控制
*/
#include "sem.h"

#define SEM_CONTROL_P 0
#define SEM_CONTROL_C 1

int main(void)
{
    int semid;
    pid_t pid;
    unsigned short array[] = {1,0};

    semid = create_sem(2,array);


    pid = fork();
    if(pid==-1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        for(;;)
        {
            option_sem_occupy(semid,SEM_CONTROL_C);
            printf("B");
            fflush(stdout);
            option_sem_release(semid,SEM_CONTROL_P);
        }
    }
    else if(pid>0)
    {
        for(;;)
        {
            option_sem_occupy(semid,SEM_CONTROL_P);
            printf("A");
            fflush(stdout);
            option_sem_release(semid,SEM_CONTROL_C);
            option_sem_occupy(semid,SEM_CONTROL_P);
            printf("A\n");
            sleep(1);
            option_sem_release(semid,SEM_CONTROL_P);
        }
    }
    return 0;
}