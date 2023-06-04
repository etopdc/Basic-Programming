#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


/*
    pause() 本进程挂起暂停，等待任意信号唤醒
*/
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
        /*子进程睡眠3s，然后给父进程发一个信号*/
        
        fprintf(stdout,"Child process <%d> start...\n",getpid());
        sleep(3);
        kill(getppid(),SIGALRM);
        fprintf(stdout,"Child process <%d> end...\n",getpid()); //没有输出这句话，SIGKILL的默认处理方式是：结束进程
        exit(EXIT_SUCCESS);
    }
    else if(pid>0)
    {
        /* 主进程等待子进程发出的信号唤醒*/
        int ret=0;
        printf("father process <%d> start...\n",getgid());
        ret = pause();

        if(ret==-1)
        {
            perror("[ERROR] pause(): ");
            exit(EXIT_FAILURE);
        }
        printf("father process <%d> end...\n",getgid());
        exit(EXIT_SUCCESS);
    }
    return 0;
}