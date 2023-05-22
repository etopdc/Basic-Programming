#ifndef __LINKLISTH_H__
#define __LINKLISTH_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}linklist;

extern linklist *create_empty_linklist();
extern void insert_head_linklist(linklist *l, datatype data);
extern void insert_tail_linklist(linklist *l, datatype data);
extern int printf_data_linklist(linklist *l);
extern int is_empty_linklist(linklist *l);
extern void remove_data_linklist(linklist *l, datatype data);
extern void reverse_linklist(linklist *l);
#endif