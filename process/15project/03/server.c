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
    shm_fifo_t *shm_fifo;
    person_t person;

    shm_fifo = shm_fifo_create(3,sizeof(person_t));
    
    for(;;)
    {
        shm_fifo_get(shm_fifo, &person);
        printf("age=%d,name=%s\n",person.age,person.name);
    }
    return 0;

}