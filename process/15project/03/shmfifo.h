#ifndef __SHMFIFO_H_ 
#define __SHMFIFO_H_ 

#include "shm.h"
#include "sem.h"

typedef struct shm_head
{
    int rpos;//当前读位置
    int wpos;//当前写位置
    int blocks;//数据块个数
    int blksz;//数据块大小
    int semid;//信号量集合id
}shm_head_t;

typedef struct shm_fifo
{
    shm_head_t *p_head;
    char *p_payload;
}shm_fifo_t;

extern shm_fifo_t *shm_fifo_create(int blocks,int blksz);
extern void shm_fifo_destory(shm_fifo_t *p_shm_fifo);
extern void shm_fifo_put(shm_fifo_t *fifo,const void *buf);
extern void shm_fifo_get(shm_fifo_t *fifo, void *buf);

#endif