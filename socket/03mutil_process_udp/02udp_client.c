#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define LOGIN_SUCCESS 0
#define LOGIN_FAILURE -1

void send_data(int sockfd,struct sockaddr_in *addr,int len)
{
	int n = 0;
	char buf[1024] = {0};

	while(1)
	{
		putchar('>');	
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0'; //'\n'--->'\0'

		n = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)addr,len);
		if(n < 0)
		{
			perror("Fail to sendto");	
			exit(EXIT_FAILURE);
		}

		if(strncmp(buf,"quit",4) == 0)
			break;
	}
	return ;
}

void user_login(int sockfd,struct sockaddr_in *dest_addr,int len)
{
	int n = 0;
	char buf[1024] = {0};
	unsigned char login_flag = LOGIN_FAILURE;
	int ret;

	while(1)
	{
		putchar('>');	
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0'; //'\n'--->'\0'

		n = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)dest_addr,len);
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

//./a.out ip port
int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in dest_addr;
	int len = sizeof(dest_addr);
	int ret;
	char buf[1024] = {0};
	if(argc != 3)
	{ 
		fprintf(stderr,"Usage : %s ip port!\n",argv[0]);
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

	//发送登录信息
	user_login(sockfd,&dest_addr,len);

	//3.发送数据
	send_data(sockfd,&dest_addr,len);

	//4.关闭文件描述符
	close(sockfd);
	return 0;
}
