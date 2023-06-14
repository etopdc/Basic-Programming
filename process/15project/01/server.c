#include "shm.h"
#include <sys/types.h>
#include <string.h>

#define SHM_SZ 256
int main()
{
    enum shm_create_status status;
    int shmid;
    void *addr;
    char buffer[32]={0};

    status=shm_create(SHM_SZ,&shmid);
    if(status==SHM_CREATE_ERR)
    {
        perror("[ERROR] shmget(): \n");
        exit(EXIT_FAILURE);
    }

    addr=shm_at(shmid);

    memcpy(buffer,addr,10);

    printf("buffer=%s\n",buffer);

    shm_dt(addr);

    shm_del(shmid);
    
    return 0;
}