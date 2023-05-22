#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
/*
位域空间大小计算
*/
struct
{
    /* data */
    char a:2;
    char b:7;
    char c:4;
}st1;

 
int main()
{
    printf("sizeof(st1)=%ld\n",sizeof(st1));//3
    return 0;
}