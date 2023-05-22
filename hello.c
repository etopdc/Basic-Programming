#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
void change(int *p)
{
    int *a = (int *)malloc(sizeof(int));
    memset(a,0,sizeof(int));
    p = a;
}
int main()
{
    int p =10;
    change(&p);
    printf("%d",p);//10
    return 0;
}