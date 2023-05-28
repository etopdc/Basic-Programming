#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// 用户自定义信号处理方式
// @param sig : 当前接收到的信号（与这个处理函数相关联）
void do_sig_usr(int sig)
{
    // 将信号编号转换成字符串的形式
    printf("Receive %s \n",strsignal(sig));
}

int main(void)
{
    pid_t pid;
    __sighandler_t ret;
    // 将信号和信号处理函数(用户自定义方式)关联到内核
    ret = signal(SIGUSR1,do_sig_usr);
    if(ret==SIG_ERR)
    {
        perror("[ERROR] signal(): ");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid==-1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        /*子进程pasue 暂停，等待父进程发出的信号*/
        int retp;
        fprintf(stdout,"Child process <%d> start...\n",getpid());
        retp = pause(); // 等待信号唤醒,这里需要信号到达之前进入睡眠状态

        if(retp==-1)
        {
            perror("[ERROR] pause(): ");
            exit(EXIT_FAILURE);
        }


        fprintf(stdout,"Child process <%d> end...\n",getpid());
        exit(EXIT_SUCCESS);
    }
    else if(pid>0)
    {
        /* 主进程发出信号唤醒子进程*/
        
        printf("father process <%d> start...\n",getgid());
        sleep(3);
        kill(pid,SIGCHLD);
        wait(NULL);
        printf("father process <%d> end...\n",getgid());
        exit(EXIT_SUCCESS);
    }
    return 0;
}