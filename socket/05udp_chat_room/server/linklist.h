#ifndef __LINKLISTH_H__
#define __LINKLISTH_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

//里面存放sockaddr_in
typedef struct sockaddr_in datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}linklist;

extern linklist *create_empty_linklist();
extern void insert_head_linklist(linklist *l, datatype data);
extern int find_linklist(linklist *head,datatype *data);
#endif