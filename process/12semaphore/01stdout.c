#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
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
            printf("C==================\n");
            printf("Child process\n");
            sleep(1);
            printf("C==================\n");
            
        }
    }
    else if(pid>0)
    {
        for(;;)
        {
            printf("F==================\n");
            printf("Father process\n");
            sleep(1);
            printf("F==================\n");
            
        }
    }
    return 0;
}