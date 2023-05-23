#include <stdio.h>

//默认有三个文件流指针，stdin stdout stderr
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    char *ch;
    char buffer[64] ={0};
    if(NULL==fp)
    {
        perror("fopen():");
        return -1;
    }
    for(;;)
    {
        ch = fgets(buffer,sizeof(buffer), fp);
        if(ch == NULL)
        {
            break;
        }
        fputs(ch,stdout); // stdout行缓存
    }
    

    fclose(fp);
    return 0;
}