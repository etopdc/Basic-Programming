#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int data_type;
#define MAX 3
/*结构体定义*/
typedef struct
{
    data_type buf[10];
    int n;
} seqlist_t;

extern seqlist_t *create_empty_seqlist();
extern void insert_data_seqlist(seqlist_t *l, data_type data);
extern void printf_data_seqlist(seqlist_t *l);
extern int is_full_seqlist(seqlist_t *l);
extern int remove_data_seqlist(seqlist_t *l, data_type data);
extern int is_empty_seqlist(seqlist_t *l);
#endif