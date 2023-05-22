#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
int main()
{
    printf("\033[2J");
    printf("\033[5;6H");
    printf("\033[44;31m");
    printf("\033[?25l");
    printf("hello world!\n");
    printf("\033[0m");
    return 0;
}