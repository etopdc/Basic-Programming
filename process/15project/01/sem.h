#ifndef __SEM_H_
#define __SEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

extern int create_sem(int nsems, unsigned short array[]);
extern int option_sem_occupy(int semid, unsigned short semnum);
extern int option_sem_release(int semid, unsigned short semnum);
extern int del_sem(int semid);

#define SEM_SET_PATHNAME "."
#define SEM_SET_PRO_ID 88

#endif