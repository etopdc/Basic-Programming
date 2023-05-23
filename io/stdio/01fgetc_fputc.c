#include <stdio.h>

//默认有三个文件流指针，stdin stdout stderr
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    char ch;
    if(NULL==fp)
    {
        perror("fopen():");
        return -1;
    }
    for(;;)
    {
        ch = fgetc(fp);
        if(ch == EOF)
        {
            break;
        }
        fputc(ch,stdout); // stdout行缓存
    }
    

    while(1){}

    fclose(fp);
    return 0;
}