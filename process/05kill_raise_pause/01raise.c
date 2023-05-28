#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        fprintf(stdout,"Child process <%d> running\n",getpid());
        raise(SIGSTOP);  // 给进程本身发送信号 SIGSTOP
        fprintf(stdout,"Child process <%d> exit\n",getpid()); //没有输出这句话，SIGKILL的默认处理方式是：结束进程
        exit(EXIT_SUCCESS);
    }
    else if(pid>0)
    {
        int status,ret;
        sleep(1); // 让父进程执行的慢一点，子进程先执行
        ret = kill(pid,SIGKILL);  // 父进程给子进程发送KILL信号
        if(ret==0)
        {
            fprintf(stdout,"Father %d killed child process %d\n",getpid(),pid);
        }
        waitpid(-1,NULL,0);  //阻塞等待

        fprintf(stdout,"father process <%d> exit\n",getpid());
        exit(EXIT_SUCCESS);
    }
    return 0;
}