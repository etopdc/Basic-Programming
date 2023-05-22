#include "linkstack.h"


//1.创建空的链式栈——为栈头在堆区分配空间

linkstack_t *create_empty_linkstack()
{
	linkstack_t *s = NULL;

	s = (linkstack_t *)malloc(sizeof(linkstack_t));
	if(NULL == s)
	{
		printf("malloc is fail!\n");	
		return NULL;
	}

	memset(s,0,sizeof(linkstack_t));

	return s;
}


//2.判断栈是否为空
int is_empty_linkstack(linkstack_t *s)
{
	return s->top == NULL ? 1 : 0;
}

//3.入栈
void push_linkstack(linkstack_t *s,data_t data)
{
	linknode_t *temp = NULL;	

	temp = (linknode_t *)malloc(sizeof(linknode_t));
	if(NULL == temp)
	{
		printf("malloc is fail!\n");	
		return ;
	}

	temp->data = data;

	//插入数据，类似于链表的头插法
	temp->next = s->top;
	s->top = temp;

	//更新n的值
	s->n ++;
	return ;
}

//4.出栈
data_t pop_linkstack(linkstack_t *s)
{
	linknode_t *temp = NULL;
	data_t data;


	//1.保存要删除结点的地址
	temp = s->top;

	//2.取出数据
	data = temp->data;

	//3.更新指针信息
	s->top = temp->next;

	//4.释放temp结点
	free(temp);
	temp = NULL;

	//5.更新n的值
	s->n --;

	return data;
}

//5.输出栈顶元素的值
data_t get_top_data(linkstack_t *s)
{
	return s->top->data;
}
