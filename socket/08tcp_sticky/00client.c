#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in serv_addr;
    int ret;
	int length;
	char buf[] = "hello server";
	char *pbuffer;
	int sbytes;

	if(argc != 3)
	{ 
		fprintf(stderr,"Usage : %s ip port!\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	//1.通过socket创建文件描述符
	sockfd = socket(AF_INET,SOCK_STREAM,0); // (地址族，TCP协议类型，协议编号)
	if(sockfd < 0)
	{
		perror("Fail to socket!");	
		return -1;
	}

	//2.填充服务器的ip + port
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);


	//3.连接服务器
	ret = connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(ret==-1)
    {
		fprintf(stderr,"[ERROR] socket connect error = %d(%s)",errno,strerror(errno));
        // perror("[ERROR] connect(): ");
        exit(EXIT_FAILURE);
    }
	printf("connect success!\n");
	
	for(;;)
	{
		
		length = strlen(buf);
		sbytes=0;
		sbytes = send(sockfd,buf,length,0);
		
		if(sbytes==-1)
		{
			fprintf(stderr,"[ERROR] send() : %d(%s)",errno,strerror(errno));
        	exit(EXIT_FAILURE);
		}
	}

	//4.关闭文件描述符
	close(sockfd);
	return 0;
}