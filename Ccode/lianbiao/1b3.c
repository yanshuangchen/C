#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 定义一个list_node的结构体，里面存放了数据域和指针域*/
struct list_node
{
	int data ; 
	struct list_node *next ;
};
// 起别名 
typedef struct list_node list_single ; 	
// 封装函数
list_single *create_list_node(int data)
{
	list_single *node = NULL ;
	node = (list_single *)malloc(sizeof(list_single));
	if(node == NULL){
		printf("malloc fair!\n");
	}
	memset(node,0,sizeof(list_single));
	node->data = data;
	node->next = NULL ;
	return node ;
}
// 主函数
int main(void)
{
	int data = 100 ;
	list_single *node_ptr = create_list_node(data); //创建一个节点
	printf("node_ptr->data=%d\n",node_ptr->data);   //打印节点里的数据
	printf("node_ptr->next=%d\n",node_ptr->next);  
	free(node_ptr);
	return 0 ;
}