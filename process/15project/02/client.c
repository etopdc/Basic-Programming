#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shmfifo.h"

typedef struct person
{
    int age;
    char name[32];
}person_t;

int main()
{
    pid_t cpid;
    shm_fifo_t *shm_fifo;

    shm_fifo = shm_fifo_create(3,sizeof(person_t));
    cpid = fork();
    if(cpid==-1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }
    else if(cpid==0)
    {
        for(int i=0;i<10;i++)
        {
            person_t person;
            strcpy(person.name,"zhangsan");
            person.age=13;
            shm_fifo_put(shm_fifo,&person);
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    }
    else if(cpid>0)
    {
        cpid = fork();
        if(cpid==-1)
        {
            perror("[ERROR] fork(): ");
            exit(EXIT_FAILURE);
        }
        else if(cpid==0)
        {
            for(int i=0;i<10;i++)
            {
                person_t person;
                strcpy(person.name,"lisi");
                person.age=26;
                shm_fifo_put(shm_fifo,&person);
                sleep(2);
            }
            exit(EXIT_SUCCESS);
        }
        else if(cpid>0)
        {
            wait(NULL);
            wait(NULL);
        }
    }

}