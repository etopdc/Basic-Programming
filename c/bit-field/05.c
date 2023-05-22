#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
struct
{
    /* data */
    unsigned int a:12;
    unsigned char b:4;
    unsigned int c:4;
}st1;

struct
{
    /* data */
    unsigned int a:12;
    unsigned int b;
    unsigned int c:4;
}st2;

 
int main()
{
    printf("sizeof(st1)=%ld\n",sizeof(st1)); //4
    printf("sizeof(st2)=%ld\n",sizeof(st2)); //12
    return 0;
}