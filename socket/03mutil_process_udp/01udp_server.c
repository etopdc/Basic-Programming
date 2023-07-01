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

#define LOGIN_SUCCESS 0
#define LOGIN_FAILURE -1

int init_socket(const char *ip,const char *port)
{
    int socketfd;
    struct sockaddr_in my_addr;
    int addrlen = sizeof(my_addr);

    //创建socket文件描述符
    socketfd = socket(AF_INET,SOCK_DGRAM,0); // (地址族，协议类型，协议编号)
    if(socketfd==-1)
    {
        perror("[ERROR] socket(): ");
        exit(EXIT_FAILURE);
    }

    //填充自己的ip和port
    memset(&my_addr,0,sizeof(struct sockaddr_in));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(port));
    my_addr.sin_addr.s_addr = inet_addr(ip);

    //绑定
    if(bind(socketfd,(struct sockaddr *)&my_addr,addrlen)<0)
    {
        perror("[ERROR] bind(): ");
        exit(EXIT_FAILURE);
    }
    return socketfd;
}

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
        memset(&buf,0,sizeof(buf));
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
    close(socketfd);
    exit(EXIT_SUCCESS);
}

int user_login(const char *ip, const char *port)
{
    int socketfd;
    char buf[1024]={0};
    struct sockaddr_in dest_addr;
    int addrlen = sizeof(dest_addr);
    unsigned char login_flag;
    int ret;

    //创建socket套接字
    socketfd = init_socket(ip,port);

    while(1)
    {
        // 接收登录数据 成功：接受字节数  失败：-1
        memset(&dest_addr,0,addrlen);
        ret = recvfrom(socketfd,buf,sizeof(buf),0,(struct sockaddr *)&dest_addr,&addrlen);
        if(ret==-1)
        {
            fprintf(stderr,"[ERROR] recvfrom(): %s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }
        
        printf("key = %s\n",buf);

        login_flag = (strncmp(buf,"root",4) == 0) ? LOGIN_SUCCESS : LOGIN_FAILURE;

        if(login_flag==LOGIN_SUCCESS)
        {
            //创建子进程，接收数据
            if(fork()==0)
            {
                close(socketfd);
                //创建socket文件描述符
                socketfd = init_socket(ip, "0");
                //返回登录成功的消息
                ret = sendto(socketfd,&login_flag,sizeof(login_flag),0,(struct sockaddr *)&dest_addr,addrlen);
                if(ret==-1)
                {
                    fprintf(stderr,"[ERROR] sendto(): %s\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                break; 
            }
        }
        else 
        {
            //返回登录失败的信息
            ret = sendto(socketfd,&login_flag,sizeof(login_flag),0,(struct sockaddr *)&dest_addr,addrlen);
            if(ret==-1)
            {
                fprintf(stderr,"[ERROR] sendto(): %s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
    }
    return socketfd;
}

void *sig_handler(void *arg)
{
	waitpid(-1,NULL,WNOHANG);
	printf("recv signum = %d zombie\n",signum);
	return;
}
// ./a.out ip port
int main(int argc,char *argv[])
{
    int socketfd;

    if(argc!=3)
    {
        fprintf(stderr,"Usage : %s ip port",argv[0]);
        exit(EXIT_FAILURE);
    }

    //0.主进程回收僵尸态子进程
	if(signal(SIGCHLD,sig_handler) == SIG_ERR)
	{
		perror("Fail to signal");	
		return -1;
	}
    
    //1.登录，判断秘钥是否正确
    socketfd = user_login(argv[1], argv[2]);

    //2.接收数据
    recv_data(socketfd);

    //3.关闭文件描述符
    close(socketfd);
    return 0;
}