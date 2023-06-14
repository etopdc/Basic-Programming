#include "shm.h"
#include <sys/types.h>
#include <string.h>

#define SHM_SZ 256
int main()
{
    enum shm_create_status status;
    int shmid;
    void *addr;

    status=shm_create(SHM_SZ,&shmid);
    if(status==SHM_CREATE_ERR)
    {
        exit(EXIT_FAILURE);
    }

    addr=shm_at(shmid);

    memset(addr,'A',10);//设置共享内存前十个字节

    shm_dt(addr);

    //shm_del(shmid);
    
    return 0;
}