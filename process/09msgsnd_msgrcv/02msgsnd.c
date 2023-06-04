#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
    使用消息队列发送数据
*/

/*
    ftok(pathname, pro_id)  创建 ipc对象唯一id
    msgget(key, flag)   创建消息队列
    msgsnd()
*/

//创建消息需要
#define PATHNAME "."
#define PRO_ID 88
//发送消息需要
#define MSG_SZ 64
struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[MSG_SZ];    /* message data */
};



int main(void)
{
    key_t key;

    int msgid,ret;
    key = ftok(PATHNAME, PRO_ID); //合成key
    if(key==-1)
    {

    }
    msgid = msgget(key, IPC_CREAT|0644);  // 创建消息id
    if(msgid==-1)
    {

    }
    fprintf(stdout,"msg: %d\n",msgid);

    struct msgbuf msgbuf;
    msgbuf.mtype = 101;
    strcpy(msgbuf.mtext, "hello msgsnd and msgrcv");

    ret = msgsnd(msgid, (char *)&msgbuf, sizeof(msgbuf.mtext), 0);
    if(ret==-1)
    {

    }
    #if 0
    ret = msgctl(msgid,IPC_RMID,NULL);
    if(ret==-1)
    {
        
    }
    #endif

    return 0;
}