#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int ret=0;
#if 0
    ret=execl("/bin/ls","ls","-l",NULL); //(路径，命令，参数（以NULL结尾)）
    if(ret==-1)
    {
        perror("[ERROR] execl(): ");
        exit(EXIT_FAILURE);
    }
    printf("execl process!");
#endif
#if 0
    char *const argv[] ={"ls","-l",NULL}; （参数（以NULL结尾)）
    ret=execv("/bin/ls",argv);  //(路径，命令数组）
    if(ret==-1)
    {
        perror("[ERROR] execl(): ");
        exit(EXIT_FAILURE);
    }
#endif

    ret = execlp("ls","ls","-l",NULL);  //只需要指定可执行文件名，但是要通过path环境可以找到
    if(ret==-1)
    {
        perror("[ERROR] execl(): ");
        exit(EXIT_FAILURE);
    }
    return 0;
}