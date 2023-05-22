#include "seqstack.h"

//创建空栈
seqstack_t *create_empty_seqstack()
{
    seqstack_t *s = (seqstack_t *)malloc(sizeof(seqstack_t));
    if(NULL==s)
    {
        printf("malloc failed!");
        return NULL;
    }
    //初始化
    memset(s,0,sizeof(seqstack_t));
    s->top = -1;
    return s;
}

//判断栈满
int is_full_seqstack(seqstack_t *s)
{
    return (s->top == MAX -1)?1:0;
}

//入栈
void push_seqstack(seqstack_t *s, datatype_t data)
{
    s->buf[++s->top] = data;
}

//出栈
datatype_t pop_seqstack(seqstack_t *s)
{
    datatype_t data = s->buf[s->top--];
    return data;
}

//判断栈空
int is_empty_seqstack(seqstack_t *s)
{
    return (s->top == -1)?1:0;
}

//获取栈顶元素
datatype_t get_top_seqstack(seqstack_t *s)
{
    datatype_t data = s->buf[s->top];
    return data;
}

