#ifndef __LOOPQUEUE_H__
#define __LOOPQUEUE_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 5

typedef struct
{
	data_t buf[N]; //定义数组存储数据

	int front; //队头元素的下标
	int rear; //队尾元素下一个元素的下标
}loopqueue_t;

#endif
