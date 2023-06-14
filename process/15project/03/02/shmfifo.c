#include "shmfifo.h"

#define SEM_EMPTY_ID 0
#define SEM_FULL_ID 1
#define SEM_MUTEX_ID 2

static int shmid;//共享内存id
/*
    创建环形的共享内存队列
    @param blocks:数据块个数
    @param blksz:数据块大小
*/
shm_fifo_t *shm_fifo_create(int blocks,int blksz)
{
    enum shm_create_status shm_status;
    size_t shm_sz;
    unsigned short array[3] = {0,blocks,1};

    shm_fifo_t *p_shm_fifo = (shm_fifo_t *)malloc(sizeof(shm_fifo_t));
    if(!p_shm_fifo)
        return NULL;

    shm_sz = blocks * blksz + sizeof(shm_head_t);
    shm_status = shm_create(shm_sz, &shmid);

    if(shm_status != SHM_CREATE_ERR)
    {
        p_shm_fifo->p_head = (shm_head_t *)shm_at(shmid);
        if(shm_status == SHM_CREATE_NEW)
        {
            p_shm_fifo->p_head->rpos=0;
            p_shm_fifo->p_head->wpos=0;
            p_shm_fifo->p_head->blocks=blocks;
            p_shm_fifo->p_head->blksz=blksz;
            p_shm_fifo->p_head->semid=create_sem(3, array);//信号量id
        }
        p_shm_fifo->p_payload = (char *)(p_shm_fifo->p_head +1);

        return p_shm_fifo;
    }
    return NULL;
}

/*
    删除共享内存队列
    @param p_shm_fifo: 队列首地址
*/
void shm_fifo_destory(shm_fifo_t *p_shm_fifo)
{
    del_sem(p_shm_fifo->p_head->semid);
    shm_dt(p_shm_fifo->p_head);
    shm_del(shmid);
    free(p_shm_fifo);
}
/*
    入队
*/
void shm_fifo_put(shm_fifo_t *fifo,const void *buf)
{
    int pos;

    option_sem_occupy(fifo->p_head->semid,SEM_FULL_ID);//判满
    option_sem_occupy(fifo->p_head->semid,SEM_MUTEX_ID);

    pos = fifo->p_head->blksz * fifo->p_head->wpos;//偏移量

    memcpy(fifo->p_payload + pos,buf,fifo->p_head->blksz);

    fifo->p_head->wpos = (fifo->p_head->wpos +1)%(fifo->p_head->blocks);

    option_sem_release(fifo->p_head->semid,SEM_MUTEX_ID);
    option_sem_release(fifo->p_head->semid,SEM_EMPTY_ID);
}
/*
    出队
*/
void shm_fifo_get(shm_fifo_t *fifo, void *buf)
{
    int pos;

    option_sem_occupy(fifo->p_head->semid,SEM_EMPTY_ID);//判空
    option_sem_occupy(fifo->p_head->semid,SEM_MUTEX_ID);

    pos = fifo->p_head->blksz * fifo->p_head->rpos;//偏移量

    memcpy(buf, fifo->p_payload + pos,fifo->p_head->blksz);

    fifo->p_head->rpos = (fifo->p_head->rpos +1)%(fifo->p_head->blocks);

    option_sem_release(fifo->p_head->semid,SEM_MUTEX_ID);
    option_sem_release(fifo->p_head->semid,SEM_FULL_ID);
}
