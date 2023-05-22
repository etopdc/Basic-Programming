#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct
{
    /* data */
    unsigned int a:3;

}st1,*st3;

 
int main()
{
    printf("sizeof(st1)=%ld\n",sizeof(st1));
    st1.a = 7;
    printf("a=====%d\n",st1.a);
    //st1.a = 8; /*error，8-------> 1000，超过位域*/

    return 0;
}