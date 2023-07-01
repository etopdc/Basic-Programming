#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

#include "shmfifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct tpool_task{
	void (*function)(void *arg);//任务执行函数
	void *arg;//函数变量
}tpool_task_t;

typedef struct tpool{
	tpool_task_t *tp_task; //指向任务队列空间指针

	int tp_qcapacity;//任务队列长度
	int tp_qsize;//当前任务数量

	int tp_qfront;//任务队列队头
	int tp_qrear;//任务队列队尾
	pthread_t *tp_work_thread_ids;//工作线程id数组

	int tp_number_of_threads;//总的线程数量

	pthread_mutex_t tp_mutex_pool;//线程池互斥锁

	pthread_cond_t tp_cond_empty;//条件变量：任务队列是否为空
	pthread_cond_t tp_cond_full;//条件变量：任务队列是否为满

	bool tp_shutdown;//是否销毁线程
}tpool_t;
extern tpool_t *thread_pool_init(int tp_number_of_threads, int tp_qsize);
void *tp_worker(void *arg);
extern void *thread_pool_add_task(tpool_t *pool,void (*task)(void *arg),void *arg);
#endif