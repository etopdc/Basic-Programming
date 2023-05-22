#include "seqlist.h"

// 1.创建一个空的顺序表，为结构体在堆区分配空间
seqlist_t *create_empty_seqlist()
{
    seqlist_t *l = (seqlist_t *)malloc(sizeof(seqlist_t));
    if (NULL == l)
    {
        printf("malloc is faile!\n");
        return NULL;
    }
    memset(l, 0, sizeof(seqlist_t));
    l->n = 0;
    return l;
}

// 2.插入数据
void insert_data_seqlist(seqlist_t *l, data_type data)
{
    l->buf[l->n] = data;
    l->n++;
    return;
}

// 3.输出数据
void printf_data_seqlist(seqlist_t *l)
{
    int i = 0;
    for (; i < l->n; ++i)
    {
        printf("%d ", l->buf[i]);
    }
    printf("\n");
}

// 4.判断顺序表是否为满
int is_full_seqlist(seqlist_t *l)
{
    return l->n == MAX ? 1 : 0;
}

// 5.判断是否为空
int is_empty_seqlist(seqlist_t *l)
{
    return l->n == 0 ? 1 : 0;
}

// 6. 删除元素
int remove_data_seqlist(seqlist_t *l, data_type data)
{
    int i, j = 0;
    if (is_empty_seqlist(l))
    {
        printf("seqlist is empty!\n");
        return -1;
    }
    for (i = 0; i < l->n; ++i)
    {
        if (l->buf[i] != data)
        {
            l->buf[j] = l->buf[i];
            j++;
        }
    }
    l->n = j;
    if (i == j)
    {
        printf("data is not exist!\n");
        return -2;
    }
    else
    {
        printf("data %d is being deleted!\n", data);
    }
    return 0;
}
