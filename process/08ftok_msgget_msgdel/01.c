#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATHNAME "."
#define PRO_ID 88

/*
    ftok(pathname, pro_id)  创建 ipc对象唯一id
    msgget(key, flag)   创建消息队列
*/
int main(void)
{
    key_t key;

    int msgid,ret;
    key = ftok(PATHNAME, PRO_ID);
    if(key==-1)
    {

    }
    msgid = msgget(key, IPC_CREAT|0644);
    if(msgid==-1)
    {

    }
    fprintf(stdout,"msg: %d\n",msgid);

    ret = msgctl(msgid,IPC_RMID,NULL);
    if(ret==-1)
    {
        
    }

    return 0;
}