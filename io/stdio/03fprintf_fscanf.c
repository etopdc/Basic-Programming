#include <stdio.h>
int main(int argc, char *argv[])
{
    FILE *fp;
    int a,b,c=100;
    if(argc != 2)
    {
        fprintf(stderr, "Usage : %s <pathname> \n",argv[0]);
        return -1;
    }
    fp = fopen(argv[1],"w+");
    if(NULL==fp)
    {
        perror("error fopen:");
        return -1;
    }
    //输出到标准输出 stdout
    printf("%d-%d-%d",a,b,c);

    //输出到文件流
    fprintf(fp,"%d-%d-%d",a,b,c);

    //输出到缓存
    char buffer[64] = {0};
    sprintf(buffer,"%d-%d-%d",a,b,c);
    printf("%s",buffer);

    fclose(fp);

    printf("==================\n");
    // 从标准输入 stdin 输入
    a,b,c=0;
    scanf("%d%d%d",&a,&b,&c);
    printf("a=%d,b=%d,c=%d",a,b,c);

    // 从其他文件流输入
    a,b,c=0;
    fp = fopen(argv[1],"r");
    fscanf(fp,"%d-%d-%d",&a,&b,&c);
    printf("a=%d,b=%d,c=%d",a,b,c);
    fclose(fp);
    //从缓存中输入
    sscanf(buffer, "%d-%d-%d",&a,&b,&c);
    printf("a=%d,b=%d,c=%d",a,b,c);














    return 0;
}