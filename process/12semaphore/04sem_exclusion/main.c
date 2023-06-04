#include "sem.h"



int main(void)
{
    int semid;
    pid_t pid;
    unsigned short array[] = {1};

    semid = create_sem(1,array);


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
            option_sem_occupy(semid,0);
            printf("==================\n");
            printf("Child start\n");
            sleep(1);
            printf("Child end\n");
            option_sem_release(semid,0);
            
        }
    }
    else if(pid>0)
    {
        for(;;)
        {
            option_sem_occupy(semid,0);
            printf("==================\n");
            printf("Father start\n");
            sleep(1);
            printf("Father end\n");
            option_sem_release(semid,0);
        }
    }
    return 0;
}