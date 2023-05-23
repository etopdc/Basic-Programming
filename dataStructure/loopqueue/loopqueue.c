#include "loopqueue.h"

//创建空队
loopqueue_t *create_empty_loopqueue()
{
    //分配空间
    loopqueue_t *q = NULL;
    q=(loopqueue_t *)malloc(sizeof(loopqueue_t));
    if(NULL==q)
    {
        printf("malloc failed!");
        return NULL;
    }
    //初始化
    memset(q,0,sizeof(loopqueue_t));
    q->front = 0;
    q->rear = 0;
    return q;
}

//判空
int is_empty_queue(loopqueue_t *q)
{   
    return (q->front == q->rear)?1:0;
}

//判满
int is_full_queue(loopqueue_t *q)
{
    retrun ((q->rear+1)%N == q->front)?1:0;
}

//插入元素
insert_data_queue(loopqueue_t *q, data_t data)
{
    if(is_full_queue(q))
    {
        return -1;
    }
    q->buf[q->rear] = data;
    q->rear = (q->rear+1)%N;
}

//出队
data_t delete_data_queue(loopqueue_t *q)
{
    data_t data;
    data = q->buf[q->front];
    q->front = (q->front+1)%N;
    return data;
}