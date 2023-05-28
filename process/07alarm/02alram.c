#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
    子进程结束时，会自动向父进程发送 SIGCHLD 信号
*/

// 自定义信号处理函数
void do_sig_user(int signal)
{
    /* SIGCHLD默认的处理是 忽略的 */
    fprintf(stdout,"Receive signal <%s>\n",strsignal(signal));
    wait(NULL); //这样处理既不会阻塞，还可以立即释放子进程的资源
}

int main(void)
{
    // 向内核注册 自定义函数
    __sighandler_t sigret;
    sigret = signal(SIGCHLD,do_sig_user);
    if(sigret==SIG_ERR)
    {
        perror("[ERROR] signal(): ");
        exit(EXIT_FAILURE);
    }

    // 创建子进程
    pid_t cpid = fork();
    if(cpid==-1)
    {   
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }else if(cpid==0)
    {
        printf("Child process is running...\n");
        exit(EXIT_SUCCESS);
    }
    else if(cpid>0)
    {
        while(1)
        {

        }

    }

    
    
}