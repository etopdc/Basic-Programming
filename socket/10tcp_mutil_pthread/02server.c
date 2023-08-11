#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <pthread.h>

#define BACKLOG 10

void *do_pthread(void *arg)
{
	char buf[1024]={0};
	int length, total_receive,bytes;
	int accept_fd = *(int *)arg;
	for(;;)
	{
		length=0;
		total_receive=0;
		memset(buf,0,strlen(buf));
		bytes = recv(accept_fd, &length, 4, 0);
		if(bytes==-1)
		{
			perror("[ERROR] recv()");
        	exit(EXIT_FAILURE);
		}
		else if(bytes==0)
		{
			break;
		}
		for(;;)
		{
			bytes = recv(accept_fd, buf + total_receive, length-total_receive, 0);
			if(bytes==-1)
			{
				perror("[ERROR] recv()");
        		exit(EXIT_FAILURE);
			}
			else if(bytes>0)
			{
				total_receive += bytes;
				if(total_receive==length)
				{
					break;
				}
			}
			else if(bytes==0)
			{
				printf("The client has been shutdown.\n");
				break;
			}
		}
		printf("> recv %d bytes : %s\n", bytes,buf);
	}
	close(accept_fd);
	pthread_exit(NULL);
}

void do_sigchild(int signum)
{
	wait(NULL);
}

int main(int argc, const char *argv[])
{
	int sockfd, accept_fd;
	struct sockaddr_in serv_addr,client_addr;
    int ret;
	int len;
	pthread_t pid;

	if(argc != 3)
	{ 
		fprintf(stderr,"Usage %s ip port!\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	//1.通过socket创建文件描述符
	sockfd = socket(AF_INET,SOCK_STREAM,0); // (地址族，协议类型，协议编号)
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


	//3.绑定服务器地址
	ret = bind(sockfd,(const struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
    if(ret==-1)
    {
        perror("[ERROR] bind()");
        exit(EXIT_FAILURE);
    }

	//4.监听
	ret = listen(sockfd, BACKLOG);
	if(ret==-1)
    {
        perror("[ERROR] listen()");
        exit(EXIT_FAILURE);
    }
	for(;;)
	{
		//5.接受连接
		len = sizeof(struct sockaddr);
		accept_fd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
		if(accept_fd==-1)
    	{
    	    perror("[ERROR] accept()");
    	    exit(EXIT_FAILURE);
    	}

		printf("accept from ip %s  port %d\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

		ret = pthread_create(&pid, NULL, do_pthread, (void *)&accept_fd);
		if(ret==-1)
		{
			perror("[ERROR] pthread_create()");
    	    exit(EXIT_FAILURE);
		}
		//进程由系统自动回收资源
		pthread_detach(pid);
	}
	//4.关闭文件描述符
	close(sockfd);
	return 0;
}