#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    pid_t cpid;
    int ret;
    int pipefd[2]; // 文件描述符

    ret = pipe(pipefd);  // pipe 父子进程通信
    if (ret == -1)
    {
        perror("[ERROE] pipe(): ");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }
    else if (cpid == 0) // 子进程，从管道中读取数据
    {
        char buffer[64]={0};
        int rbyte = read(pipefd[0],buffer,sizeof(buffer)); // fd[0]读端
        if(rbyte==-1)
        {
            perror("[ERROR] read(): ");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
        printf("Child process <%s>",buffer);
        close(pipefd[1]);
    }
    else if (cpid > 0) // 父进程，从管道中写数据
    {
        char buffer[] = "hello pipe.";
        int wbyte = write(pipefd[1],buffer,sizeof(buffer));  // fd[1]写端
        if(wbyte==-1)
        {
            perror("[ERROR] write(): ");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        wait(NULL);
        close(pipefd[0]);
    }

    return 0;
}