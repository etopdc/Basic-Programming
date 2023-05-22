
#ifndef __SEQSTACK_H__
#define __SEQSTACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype_t;

#define MAX 10

typedef struct 
{
    /* data */
    datatype_t buf[MAX];
    int top;
}seqstack_t;

extern seqstack_t *create_empty_seqstack();
extern void push_seqstack(seqstack_t *s, datatype_t data);
extern datatype_t get_top_seqstack(seqstack_t *s);

#endif