#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
struct
{
    /* data */
    char a:4;
    char :4 ;//空域
    char c:4; /*从下一单元开始存放*/
    char d:4;
}st1;

 
int main()
{
    printf("sizeof(st1)=%ld\n",sizeof(st1));
    return 0;
}