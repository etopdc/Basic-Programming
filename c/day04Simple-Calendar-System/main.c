#include <stdio.h>
#include<string.h>
#include<stdlib.h>


int Isleap(int y, int m, int d)
{
    if(((y%4==0)&&(y%100==0))||(y%400==0))
    {
        printf("%d年%d月%d日是闰年\n",y,m,d);
        return 1;
    }
    else
    {
        printf("%d年%d月%d日不是闰年\n",y,m,d);
    }
    return 0;
}
/*统计天数*/
int max_day(int y, int m, int d)
{
    int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int sum_day = 0;
    int arr_sum = 0;
    for(int i = 0;i<m;i++)
    {
        arr_sum += months[i];
    }
    if(Isleap(y,m,d))
    {
        sum_day = arr_sum + 1 +d;
    }
    else
    {
        sum_day = arr_sum +d;
    }
    return sum_day;
}
/*判断天数*/
int Total_day(int y, int m, int d)
{
    int sum_day = 0;
    int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    sum_day = max_day(y,m,d);
    return sum_day;
}
/*展示星期*/
int display_week(int y, int m, int d)
{
    int w = 0;
    if((m==1)||(m==2))
    {
        m += 1;
    }
    w = (d + 2*m +3*(m+1)/5+y+y/4-y/100+y/400+1)%7;
    return w;
}

/*显示日历*/
int display_month(int y, int m, int d)
{
    printf("\t\t\t%d年%d月\t\t\t\n",y,m);
    printf("SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n");
    int week = 0;
    int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    week = display_week(y,m,1);
    for(int i=0;i<week;i++)
    {
        printf("\t");        
    }
    for(int i=1;i<=months[m];i++)
    {
        printf("%d\t",i);
        if((week+i)%7==0)
        {
          printf("\n");  
        }
    }
    printf("\n");
    return 0;
}
 
int main()
{
    int y,m,d = 0;
    scanf("%d%d%d",&y,&m,&d);
    int sum_day = Total_day(y,m,d);
    printf("%d年%d月%d日是这一年%d天\n",y,m,d,sum_day);
    int week = display_week(y,m,d);
    printf("%d年%d月%d日是星期%d\n",y,m,d,week);
    display_month(y,m,d);
}