#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
int main()
{
    printf("\033[44;31m");
    printf("hello world!\n");
    printf("\033[0m");
    printf("\033[43;31mhellow world!\n\033[0m");
    return 0;
}