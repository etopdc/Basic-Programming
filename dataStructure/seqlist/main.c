#include "seqlist.h"
 
int main()
{
    //创建顺序表
    seqlist_t *l = create_empty_seqlist();
    data_type data = 0;
    printf("please input %d number : ",MAX);
    //插入元素
    while(!is_full_seqlist(l))
    {
        scanf("%d",&data);
        insert_data_seqlist(l,data);
    }
    // 输出元素
    printf_data_seqlist(l);
    printf("please input delete data: ");
    scanf("%d",&data);
    //删除元素
    remove_data_seqlist(l,data);
    printf_data_seqlist(l);
    //释放空间
    free(l);
    l=NULL;
    return 0;
}