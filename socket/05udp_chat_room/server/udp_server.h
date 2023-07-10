#ifndef __UDP_SERVER_H_
#define __UDP_SERVER_H_

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
#include <pthread.h>

#include "linklist.h"

#define LOGIN_SUCCESS 0
#define LOGIN_FAILURE -1

#define CLIENT_LOGIN    10     //加入服务器保存上线客户端链表
#define CLIENT_QUIT     20     //从链表中删除（客户端输入"quit"）
#define CLIENT_TALK     30     //遍历链表给其它客户端转发(客户端结果服务端转发)
#define SERVER_TALK     40     //遍历链表给所有客户端转发(服务端主动发送)
#define SERVER_QUIT     50     //遍历链表给所有客户端转发"quit"(广播信息),删除链表所有结点(服务端主动发送)

typedef struct 
{
	char type;//记录消息类型
	char name[15];//记录客户端名字
	char buf[1024];//记录客户聊天的信息
}msg_t;

typedef struct
{
    char *ip;
    unsigned char flag;
    struct sockaddr_in dest_addr;
    linklist *head;
}pthread_type;

#endif