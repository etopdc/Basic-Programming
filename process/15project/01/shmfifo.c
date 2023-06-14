#include "shmfifo.h"

#define SEM_MUTEX 0
#define SEM_FULL 1
#define SEM_EMPTY 2

/*
    创建环形的共享内存队列
    @param blocks:数据块个数
    @param blksz:数据块大小
*/
shm_fifo_t *shm_fifo_create(int blocks,int blksz)
{
    int shmid;
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
            p_shm_fifo->p_head->semid=create_sem(3, array);
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
    del_sem(p_shm_fifo->shm_head_t->semid);
    shm_dt(p_shm_fifo->shm_head_t);
    shm_del(shmid);
    free(p_shm_fifo);
}
/*
    入队
*/
void shm_fifo_put(shm_fifo_t *fifo,const void *buf);
{
    int ret;
    option_sem_occupy(fifo->p_head->semid,SEM_FULL);//判满
    option_sem_occupy(fifo->p_head->semid,SEM_MUTEX);
    strcpy((fifo->p_payload)+wpos*blksz,buf,blksz);
    fifo->p_head->wpos = (fifo->p_head->wpos +1)%blocks;
    option_sem_release(fifo->p_head->semid,SEM_MUTEX);
    option_sem_release(fifo->p_head->semid,SEM_EMPTY);
}
/*
    出队
*/
void shm_fifo_get(shm_fifo_t *fifo, void *buf)
{
    option_sem_occupy(fifo->p_head->semid,SEM_EMPTY);//判空
    option_sem_occupy(fifo->p_head->semid,SEM_MUTEX);
    strcpy(buf,(fifo->p_payload)+wpos*blksz,blksz);
    fifo->p_head->rpos = (fifo->p_head->rpos +1)%blocks;
    option_sem_release(fifo->p_head->semid,SEM_MUTEX);
    option_sem_release(fifo->p_head->semid,SEM_FULL);
}
