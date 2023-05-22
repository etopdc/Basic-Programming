#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//结点类型的设计

typedef char data_t;

typedef struct node
{
	data_t data;
	struct node *next;
}linknode_t;

//栈头类型的设计

typedef struct
{
	linknode_t *top;//栈顶指针
	int n; //记录当前栈种元素的个数
}linkstack_t;


//extern  



#endif