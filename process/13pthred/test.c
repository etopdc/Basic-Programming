#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp = fopen("a","rb");
    char buffer[10]={0};
    fseek(fp,10,SEEK_END);
    fread(buffer,sizeof(char),10000,fp);
    printf("%s",buffer);
    return 0;
}