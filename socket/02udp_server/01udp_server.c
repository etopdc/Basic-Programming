#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/**
    接收数据
    params:
        @socketfd   :   socket文件描述符
*/
void recv_data(int socketfd)
{
    char buf[1024]={0};
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    int ret=0;

    while(1)
    {
        // 接收数据 成功：接受字节数  失败：-1
        memset(&src_addr,0,addrlen);
        ret = recvfrom(socketfd,buf,sizeof(buf),0,(struct sockaddr *)&src_addr,&addrlen);
        if(ret==-1)
        {
            fprintf(stderr,"[ERROR] recvfrom(): %s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }

        printf("=========================\n");
        printf("Recv from IP = %s\n",inet_ntoa(src_addr.sin_addr));
        printf("Recv from PORT = %d\n",ntohs(src_addr.sin_port));
        printf("Recv %d bytes : %s\n",ret,buf);

        if(strncmp(buf,"quit",4)==0)
            break;
    }
    return ;
}


// ./a.out ip port
int main(int argc,char *argv[])
{
    int socketfd;
    struct sockaddr_in my_addr;
    int addrlen = sizeof(my_addr);

    if(argc!=3)
    {
        fprintf(stderr,"Usage : %s ip port",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //1.通过socket
    socketfd = socket(AF_INET,SOCK_DGRAM,0); // (地址族，协议类型，协议编号)

    //2.填充服务器自己的ip和端口
    memset(&my_addr,0,addrlen); 
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(argv[2]));
    my_addr.sin_addr.s_addr = inet_addr(argv[1]);

    //3.绑定数据
    if(bind(socketfd,(struct sockaddr *)&my_addr,addrlen)<0)
    {
        perror("[ERROR] bind(): ");
        exit(EXIT_FAILURE);
    }

    printf("wait recv data!\n");

    //4.接收数据
    recv_data(socketfd);

    //5.关闭文件描述符
    close(socketfd);
    return 0;
}