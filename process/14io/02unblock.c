#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int flags;
    flags = fcntl(0,F_GETFL);//获取文件状态标志
    flags |= O_NONBLOCK;//追加非阻塞标志
    fcntl(0,F_SETFL,flags);//重新设置文件状态标志
    sleep(1);
    char a[30]={0};
    scanf("%s",a);
    printf("a===%s\n",a);
    return 0;
}