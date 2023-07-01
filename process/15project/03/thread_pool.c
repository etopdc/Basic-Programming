#include "thread_pool.h"

/*
    线程执行函数
*/
void *tp_worker(void *arg)
{
    tpool_t *pool= (tpool_t *)arg;
    tpool_task_t tpool_task;

    for(;;)
    {
        pthread_mutex_lock(&pool->tp_mutex_pool);//获取互斥锁
        while(pool->tp_qsize==0 && !pool->tp_shutdown)//判断任务队列是否为空
        {
            pthread_cond_wait(&pool->tp_cond_empty,&pool->tp_mutex_pool);
        }
        //判断线程池是否销毁
        if(pool->tp_shutdown)
        {
            pthread_mutex_unlock(&pool->tp_mutex_pool);
            pthread_exit(NULL);
        }
        tpool_task.function = pool->tp_task[pool->tp_qfront].function;
        tpool_task.arg = pool->tp_task[pool->tp_qfront].arg;
        pool->tp_qfront = (pool->tp_qfront +1)%pool->tp_qcapacity;
        pool->tp_qsize--;

        pthread_cond_signal(&pool->tp_cond_full);
        pthread_mutex_unlock(&pool->tp_mutex_pool);
        printf("[DUBUG] thread %ld start working...\n",pthread_self());

        tpool_task.function(tpool_task.arg);//执行任务
        printf("[DEBUG] thread %ld end working...\n",pthread_self());
    }
}


/*
    添加任务到任务队列
*/
void *thread_pool_add_task(tpool_t *pool,void (*task)(void *arg),void *arg)
{
    pthread_mutex_lock(&pool->tp_mutex_pool);//获取互斥锁
    while(pool->tp_qcapacity==pool->tp_qsize&&!pool->tp_shutdown)//判断队列是否为满
    {
        pthread_cond_wait(&pool->tp_cond_full,&pool->tp_mutex_pool);
    }
    //判断线程池是否销毁
    if(pool->tp_shutdown)
    {
        pthread_mutex_unlock(&pool->tp_mutex_pool);
    }

    // 将任务添加到任务队列中
	pool->tp_task[pool->tp_qrear].function = task;
	pool->tp_task[pool->tp_qrear].arg = arg;
	pool->tp_qrear = (pool->tp_qrear + 1) % pool->tp_qcapacity;
	pool->tp_qsize++;

    pthread_cond_signal(&pool->tp_cond_empty);// 唤醒工作线程执行任务
	pthread_mutex_unlock(&pool->tp_mutex_pool);
}

/*
    线程池初始化
    @param:tp_number_of_threads 最大线程数
    @param:tp_qcapacity 最大任务数
*/
tpool_t *thread_pool_init(int tp_number_of_threads, int tp_qcapacity)
{
    int ret;

    tpool_t *pool = (tpool_t *)malloc(sizeof(tpool_t));//线程池结构对象
    if(!pool)
    {
        goto err;
    }

    pool->tp_work_thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * tp_number_of_threads);//线程空间
    if(!pool->tp_work_thread_ids)
        goto err;
    memset(pool->tp_work_thread_ids,0,sizeof(pthread_t) * tp_number_of_threads);//清零

    pool->tp_number_of_threads=tp_number_of_threads;//初始化线程数量

    ret = pthread_mutex_init(&pool->tp_mutex_pool,NULL);
    if(ret!=0)
        goto err;
    
    ret = pthread_cond_init(&pool->tp_cond_empty,NULL);
    if(ret!=0)
        goto err;

    ret = pthread_cond_init(&pool->tp_cond_full,NULL);
    if(ret!=0)
        goto err;

    pool->tp_qcapacity = tp_qcapacity;//初始化任务队列容量
    pool->tp_task= (tpool_task_t *)malloc(sizeof(tpool_task_t)*pool->tp_qcapacity);//创建任务队列空间
    if(!pool->tp_task)
        goto err;

    pool->tp_qsize=0;
    pool->tp_qfront=0;
    pool->tp_qrear=0;

    pool->tp_shutdown=false;

    for(int i=0;i<pool->tp_number_of_threads;i++)
    {
        ret = pthread_create(&pool->tp_work_thread_ids[i],NULL,tp_worker,(void *)pool);
        if(ret!=0)
        {
            fprintf(stderr,"[ERROR] pthread_create():%s\n",strerror(ret));
            goto err;
        }
        pthread_detach(pool->tp_work_thread_ids[i]);
    }

    return pool;

err:
    if(pool && pool->tp_task)
        free(pool->tp_task);
    if(pool && pool->tp_work_thread_ids)
        free(pool->tp_work_thread_ids);
    return NULL;
}

int thread_pool_destroy(tpool_t *pool)
{
	if (!pool)
		return -1;
	
	pool->tp_shutdown = true;

	for (int i = 0;i < pool->tp_number_of_threads;i++){
		pthread_cond_signal(&pool->tp_cond_empty);
	}

	if (pool->tp_task)
		free(pool->tp_task);
	
	if (pool->tp_work_thread_ids)
		free(pool->tp_work_thread_ids);
	
	pthread_mutex_destroy(&pool->tp_mutex_pool);
	pthread_cond_destroy(&pool->tp_cond_empty);
	pthread_cond_destroy(&pool->tp_cond_full);

	free(pool);

	pool = NULL;
	return 0;	
}
