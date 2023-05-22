#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct
{
    /* data */
    int a;
    int b;
}st2;

struct
{
    /* data */
    unsigned int a:2;//位域
    unsigned int b:2;//位域
}st1,*st3;

 
int main()
{
    printf("sizeof(st1)=%ld\n",sizeof(st1));
    printf("sizeof(st2)=%ld\n",sizeof(st2));
    st1.a = 1;
    st1.b = 3;
    st3->a = 1;
    st3->b = 3;
    printf("st1.a = %d\n",st1.a);
    printf("st1.b = %d\n",st1.b);
    printf("st1.b = %d\n",st3->a);
    printf("st1.b = %d\n",st3->b);
    return 0;
}