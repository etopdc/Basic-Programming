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

// 尾插入
void insert_tail_linklist(linklist *l, datatype data)
{
    // 1.申请堆区空间
    linklist *temp = (linklist *)malloc(sizeof(linklist));
    if (NULL == temp)
    {
        printf("malloc failed!\n");
        return;
    }
    // 2.存储数据
    temp->data = data;

    // 3.搜索尾指针
    linklist *p = l;
    while (p->next != NULL)
    {
        p = p->next;
    }
    temp->next = NULL;
    p->next = temp;
    return;
}

// 输出
int printf_data_linklist(linklist *l)
{
    linklist *p = l;

    while (p->next != NULL)
    {
        printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

// 非空判断
int is_empty_linklist(linklist *l)
{
    return l->next == NULL ? 1 : 0;
}

// 删除
void remove_data_linklist(linklist *l, datatype data)
{
    linklist *p = l;
    if(is_empty_linklist(p))
    {
        printf("linklist is empty!\n");
        return;
    }
    while (p->next != NULL)
    {
        linklist *q = p->next;
        if (q->data == data)
        {
            p->next = q->next;
            free(q);
            q = NULL;
        }
        else
        {
            p = p->next;
        }
    }
    return;
}

//链表转置
//思路一：头插法
void reverse_linklist(linklist *l)
{
    linklist *p = l->next->next;
    l->next->next =NULL;
    while(p)
    {
        linklist *q = p;
        p = p->next;
        q->next = l->next;
        l->next = q;
    }
    return;
}