#ifndef __LOOPQUEUE_H__
#define __LOOPQUEUE_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 5  //最大元素个数
typedef int data_t;

typedef struct
{
	data_t buf[N]; //定义数组存储数据

	int front; //队头元素的下标
	int rear; //队尾元素下一个元素的下标
}loopqueue_t;

extern loopqueue_t *create_empty_loopqueue();
extern insert_data_queue(loopqueue_t *q, data_t data);

#endif
