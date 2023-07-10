#include "udp_client.h"

#define LOGIN_SUCCESS 0
#define LOGIN_FAILURE -1

void send_data(int sockfd,struct sockaddr_in *dest_addr,int len,char *name)
{
	int n = 0;
	msg_t msg;

	while(1)
	{
		memset(&msg,0,sizeof(msg));

		putchar('>');	
		fgets(msg.buf,sizeof(msg.buf),stdin);
		msg.buf[strlen(msg.buf) - 1] = '\0'; //'\n'--->'\0'

		strcpy(msg.name,name);
		
		if(strncmp(msg.buf,"quit",4)==0)
		{
			msg.type = CLIENT_QUIT;
		}
		else
		{
			msg.type = CLIENT_TALK;
		}

		n = sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)dest_addr,len);

		if(n < 0)
		{
			perror("[ERROR] sendto(): ");	
			exit(EXIT_FAILURE);
		}

		if(msg.type == CLIENT_QUIT)
			break;
	}
	return ;
}

void user_login(int sockfd,struct sockaddr_in *dest_addr,int len,char *name)
{
	int n = 0;
	unsigned char login_flag = LOGIN_FAILURE;
	int ret;
	msg_t msg;

	while(1)
	{
		memset(&msg,0,sizeof(msg));

		putchar('>');	
		fgets(msg.buf,sizeof(msg.buf),stdin);
		msg.buf[strlen(msg.buf) - 1] = '\0'; //'\n'--->'\0'

		msg.type = CLIENT_LOGIN;
		strcpy(msg.name,name);

		n = sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)dest_addr,len);
		if(n < 0)
		{
			perror("[ERROR] sendto(): ");	
			exit(EXIT_FAILURE);
		}

		ret = recvfrom(sockfd,&login_flag,sizeof(login_flag), 0,(struct sockaddr *)dest_addr, &len);

      	if(ret==-1)
      	{
      	    fprintf(stderr,"[ERROR] recvfrom(): %s\n",strerror(errno));
      	    exit(EXIT_FAILURE);
      	}
		if(login_flag==LOGIN_SUCCESS)
		{
			printf("login success!\n");
			break;
		}
		else
		{
			printf("key is error, try again!\n");
		}

	}
	return ;
}

/**
    接收数据
    params:
        @socketfd   :   socket文件描述符
*/
void *recv_message(void *arg)
{
	int socketfd = *(int *)arg;
    msg_t msg;
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    int ret=0;

    while(1)
    {
        // 接收数据 成功：接受字节数  失败：-1
        memset(&src_addr,0,addrlen);
        memset(&msg,0,sizeof(msg));
        ret = recvfrom(socketfd,&msg,sizeof(msg),0,(struct sockaddr *)&src_addr,&addrlen);
        if(ret==-1)
        {
            fprintf(stderr,"[ERROR] recvfrom(): %s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }

        printf("============Recevie Message============\n");
        printf("Recv from IP = %s\n",inet_ntoa(src_addr.sin_addr));
        printf("Recv from PORT = %d\n",ntohs(src_addr.sin_port));
        printf("Recv %ld bytes : %s\n",sizeof(msg.buf),msg.buf);
		printf("=======================================\n");

        if(msg.type == SERVER_QUIT)
            break;
		putchar('>');
    }
	close(socketfd);
	exit(EXIT_SUCCESS);
}

//./a.out ip port
int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in dest_addr;
	int len = sizeof(dest_addr);
	int ret;
	pthread_t pid;
	char name[15]={0};

	if(argc != 4)
	{ 
		fprintf(stderr,"Usage : %s ip port name!\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	//1.通过socket创建文件描述符
	sockfd = socket(AF_INET,SOCK_DGRAM,0); // (地址族，协议类型，协议编号)
	if(sockfd < 0)
	{
		perror("Fail to socket!");	
		return -1;
	}

	//2.填充服务器的ip + port
	memset(&dest_addr,0,sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(atoi(argv[2]));
	dest_addr.sin_addr.s_addr = inet_addr(argv[1]);

	strcpy(name,argv[3]);

	//3.发送登录信息
	user_login(sockfd,&dest_addr,len,name);

	//4.创建子线程，用于接收服务器传送过来的数据
	pthread_create(&pid,NULL,recv_message,(void *)&sockfd);
	pthread_detach(pid);

	//5.发送数据
	send_data(sockfd,&dest_addr,len,name);

	//6.关闭文件描述符
	close(sockfd);
	return 0;
}
