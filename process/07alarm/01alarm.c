#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
void do_sig_user(int signal)
{
    fprintf(stdout,"signal is %s\n",strsignal(signal));
}
int main(void)
{

    __sighandler_t sigret;
    sigret = signal(SIGALRM,do_sig_user);
    if(sigret==SIG_ERR)
    {
        perror("[ERROR] signal(): ");
        exit(EXIT_FAILURE);
    }
    unsigned int ret;
    ret=alarm(3);// 设置定时时间为3s的定时器(到时间会自动向进程发出SIGALRM信号)
    pause();// 等待命令，等待信号唤醒，等待SIGALRM信号
    printf("Main process end.\n") ;
    return 0;
}