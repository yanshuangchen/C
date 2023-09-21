#include "stdio.h"
#include "windows.h"
#include "stdlib.h"

#define MAXSIZE 20  //顺序表最大长度

/*将struct通过typedef起别名生成名叫Seqlist的数据类型，比如说int起别名为L，同时这个结构体
里面包含了两个数据类型data，类型为数组和length
*/
typedef struct {
	int data[MAXSIZE];
	int length;
}SeqList;

/*初始化顺序表，通过输入结构体的地址或者说是指针来实现程序
输入了变量list的地址，即结构体的指针
所以说输入的是结构体变量*/
void InitList(SeqList *l)
{
	l->length = 0;
	// 所以初始化length的长度为0
	// 代表了(*l).length的意思
}

/*建立顺序表，通过输入原数组，和结构体变量和添加数量来创建指定个数的顺序表*/
int CreatList(SeqList *l, int a[], int n) {
	if (n > MAXSIZE)
	{
		printf("空间不够，无法建立顺序表。\n");
		return 0;
	}
	for (int k = 0; k < n; k++)
	{
		l->data[k] = a[k];
	}
	l->length = n;
	return 1;
}

/*判断length是否为0*/
int Empty(SeqList *l)
{
	if (l->length == 0)
		return 1;
	else
		return 0;
}

/*求顺序表长度*/
int Length(SeqList *l)
{
	return l->length;
}

/*遍历操作*/
void PrintList(SeqList *l)
{
	for (int i = 0; i < l->length; i++)
		printf("%d ", (l->data[i]));
}

/*按值查找*/
int Locate(SeqList *l,int x)
{
	for (int i = 0; i < l->length; i++)
	{
		if (l->data[i] == x)
		{
			return i + 1;
		}
		return 0;

	}
	return 1;
}

/*按位查找,已经修改了指针，那么指针已经被修改完毕，所以只需要找到地址即可*/

int Get(SeqList *l, int x,int *ptr)
{//若查找成功，则通过指针参数ptr返回值
	if ( x <1 || x>l->length){
		printf("查找位置非法，查找错误\n");
		return 0;
	}
	else
	{
		*ptr = l->data[x];
		return 1;
	}
}

/*插入操作，通过循环将数据插入，然后加上需要填补的值，然后将length的值加上1*/
int Insert(SeqList *l, int i, int x)
{
	if (l->length > MAXSIZE)
	{
		printf("上溢错误！");
		return 0;
	}
	if (i<1 || i>l->length)
	{
		printf("插入位置错误！");
		return 0;
	}
	for (int k = l->length; k > i; k--)
	{
		l->data[k] = l->data[k - 1];
	}
	l->data[i] = x;
	l->length++;
	return 1;
}

/*删除操作*/
int Delete(SeqList *l, int i, int *ptr)
{
	if (l->length == 0)
	{
		printf("发生下溢错误，即将要访问顺序表之前的地址.\n");
		return 0;
	}
	if (i > l->length || i < 1)
	{
		printf("删除位置错误！\n");
		return 0;
	}
	*ptr = l->data[i - 1];//把要删除的数据返回
	for (int j = i; j < l->length; j++)
	{
		l->data[j - 1] = l->data[j];
	}
	l->length--;
	return 1;
}

/*修改操作*/
int Modify(SeqList *l, int i, int x)
{
	if (i > l->length || i < 1)
	{
		printf("位置错误！\n");
		return 0;
	}
	l->data[i] = x;
	return 1;
}

int main()
{
	int a[5] = {1,2,3,4,5 };
	int  i, x;
	// 相当于int了一个变量为p，所以list1为变量
	SeqList list1;
	//通过引入函数来初始化顺序表
	InitList(&list1);
	// Empty是一个函数，返回0和1
	if (Empty(&list1))
	{
		printf("初始化顺序表成功！\n");
	}
	printf("给顺序表赋值：1 2 3 4 5\n遍历并输出顺序表：\n");
	CreatList(&list1,a,5 );//建立一个长度为5的线性表
	PrintList(&list1);//遍历输出此顺序表
	printf("\n在第三位后插入一个100：\n");
	Insert(&list1, 3, 100);
	PrintList(&list1);
	// 修改函数
	if (Modify(&list1, 3, 50) == 1) {
		printf("\n把第三位改成50\n");
		PrintList(&list1);
	}
	// 删除元素
	if (Delete(&list1, 4, &x) == 1) {
		printf("\n把第四位删除，删除的值是%d\n",x);
		PrintList(&list1);
	}
	// 暂停程序
	system("pause");
	return 0; 
}
