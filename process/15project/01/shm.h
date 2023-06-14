#ifndef __SHM_H_
#define __SHM_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

enum shm_create_status
{
    SHM_IS_EXITS =0,
    SHM_CREATE_NEW,
    SHM_CREATE_ERR,
};

extern enum shm_create_status shm_create(size_t size, int *shmid);
extern void *shm_at(int shmid);
extern int shm_dt(void *addr);
extern int shm_del(int shmid);

#endif