#include "linklist.h"

// 创建空链表
linklist *create_empty_linklist()
{
    // 1.申请空间
    linklist *l = (linklist *)malloc(sizeof(linklist));
    if (NULL == l)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    // 2.初始化
    memset(l, 0, sizeof(linklist));
    return l;
}

// 头插入
void insert_head_linklist(linklist *l, datatype data)
{
    linklist *p = l;
    // 1.申请堆区空间
    linklist *temp = (linklist *)malloc(sizeof(linklist));
    if (NULL == temp)
    {
        printf("malloc failed!\n");
        return;
    }
    // 2.存储数据
    temp->data = data;

    // 3.连接结点
    temp->next = p->next;
    p->next = temp;
    return;
}

//在链表中查找该客户端是否已经存在用户信息，存在返回1，否则返回0
int find_linklist(linklist *head,datatype *data)
{
	linklist *p = head;

	while(p->next != NULL)
	{
		//说明链表中有该用户信息，老用户
		if(memcmp(&(p->data),data,sizeof(datatype)) == 0)
			return 1;

		p = p->next;	
	}
	//若是循环结束，上面的memcmp都没有执行，说明是新用户，返回0 
	return 0;
}