#include "linklist.h"

int main()
{
    datatype data = 12;
    linklist *l = create_empty_linklist();
    insert_head_linklist(l, data);
    insert_head_linklist(l, 16);
    insert_head_linklist(l, 19);
    // printf("%p",(void *)l);
    printf_data_linklist(l);
    reverse_linklist(l);
    printf_data_linklist(l);

}