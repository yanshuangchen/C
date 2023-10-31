#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//若取出的字符是操作数，则加入后缀表达式
//若取出的字符是运算符：
// a.若为’(’，入栈；
// b.若为’)’，则依次把栈中的运算符加入后缀表达式，直到出现’(’，然后从栈中删除’(’；
// c.若为除了括号之外的其他运算符，当其优先级高于栈顶的运算符时，直接入栈；
//否则从栈顶开始，依次弹出比当前处理的运算符优先级高和优先级相等的运算符，直到遇到一个比它优先级低或遇到了一个左括号为止。

struct node
{
	char num;		   //内容
	struct node *next; //链式表，指向下一个结点
};
typedef struct node *PNODE;

struct stack //存放栈顶的结构体，即栈
{
	PNODE top;
	int size; //栈的大小
};
typedef struct stack *Stack;

//创建一个空栈
Stack createStack()
{
	Stack stack;
	stack = (Stack)malloc(sizeof(struct stack));
	if (stack != NULL)
	{
		stack->top = NULL;
		stack->size = 0;
	}
	else
		printf("Out of space!");
	return stack;
}

//判断栈是否为空栈
int isEmptyStack(Stack stack)
{
	return (stack->top == NULL);
}

//入栈操作(头插法）
void pushStack(Stack stack, char x)
{
	PNODE p;
	p = (PNODE)malloc(sizeof(struct node));
	if (p == NULL)
	{
		printf("Out of space!\n");
	}
	else
	{
		p->num = x;
		p->next = stack->top;
		stack->top = p;
		stack->size++;
	}
}

//出栈操作
char popStack(Stack stack)
{
	PNODE p;
	if (isEmptyStack(stack))
	{
		printf("Empty Stack pop!\n");
	}
	else
	{
		char ch = stack->top->num;
		p = stack->top;
		stack->top = stack->top->next;
		free(p);
		stack->size--;
		return ch;
	}
}

//取栈顶元素
char top_num(Stack stack)
{
	if (stack->top == NULL)
	{
		printf("Empty Stack!\n");
	}
	else
	{
		return (stack->top->num);
	}
}
/*
   函数名：inToPost，本函数名和参数不能更改
   函数功能：将中缀表达式转换为后缀表达式输出
   函数参数：中缀表达式，放在字符数组中
   返回值：返回放有后缀表达式的栈
*/
Stack inToPost(char *expression)
{
	//在此处填写代码，完成中缀表达式转换为后缀表达式并输出
	/**********  Begin  **********/
	Stack houzhui, fuhao;
	houzhui = createStack();
	fuhao = createStack();
	int len;
	len = strlen(expression); //得到字符串的长度
	char q = '#';
	pushStack(fuhao, q);
	for (int i = 0; i < len; i++) //遍历数组
	{
		char ch = expression[i];
		//若取出的字符是操作数，则加入后缀表达式，这里也可以是a到z加个&&就行
		if (ch > '0' && ch < '9')
		{
			if (expression[i + 1] > '0' && expression[i + 1] < '9' && i != len - 1) //如果后面一个也是操作数就不加空格，除非是最后一个数
			{
				pushStack(houzhui, ch);
			}
			else
			{

				pushStack(houzhui, ch);
				pushStack(houzhui, ' ');
			}
		}
		// a.若为’(’，入符号栈；
		else if (ch == '(')
		{
			pushStack(fuhao, ch);
		}
		// b.若为’)’，则依次把栈顶的运算符加入后缀表达式，直到出现’(’，然后从栈中删除’(’；
		else if (ch == ')')
		{
			while (fuhao->top->num != '(')
			{
				char topch = fuhao->top->num;
				popStack(fuhao);		   //出栈栈顶
				pushStack(houzhui, topch); //入栈后缀
				pushStack(houzhui, ' ');   //空格入栈，表示间隔
			}
			popStack(fuhao); //在符号栈中删除(
		}
		// c.若为除了括号之外的其他运算符，当其优先级高于栈顶的运算符时，直接入栈；
		//否则从栈顶开始，依次弹出比当前处理的运算符优先级高和优先级相等的运算符，直到遇到一个比它优先级低或遇到了一个左括号为止。

		//假如是+，-，那么栈顶遇到（,进符号栈,否则栈顶一直出栈进后缀栈
		else if (ch == '+' || ch == '-')
		{
			while (fuhao->top->num != '(')
			{
				if (fuhao->top->num == '#')
				{
					break;
				}
				char topch = fuhao->top->num;
				popStack(fuhao);		   //出符号栈栈顶
				pushStack(houzhui, topch); //入栈后缀
				pushStack(houzhui, ' ');
			}
			pushStack(fuhao, ch); //此时的符号进入符号栈
		}
		//如果是* /,如果栈顶为* /，栈顶就出栈进入后缀栈，如果是	其他就入符号栈
		else if (ch == '*' || ch == '/')
		{
			while (fuhao->top->num == '*' || fuhao->top->num == '/')
			{
				char topch = fuhao->top->num;
				popStack(fuhao);		   //出符号栈栈顶
				pushStack(houzhui, topch); //入栈后缀
				pushStack(houzhui, ' ');
			}
			pushStack(fuhao, ch); //此时的符号进入符号栈
		}
	}
	//数组遍历完，将符号栈中所有东西存入后缀栈
	while (fuhao->top->num != '#')
	{
		char topch = fuhao->top->num;
		popStack(fuhao);		   //出符号栈栈顶
		pushStack(houzhui, topch); //入栈后缀
		pushStack(houzhui, ' ');
	}
	return houzhui;

	/**********  End  **********/
}

// print函数用于输出后缀表达式，参数是 inToPost的返回值

void print(Stack s)
{
	Stack result;
	result = createStack(); //由于栈输出是逆序的，所以再来一个栈变成正序
							//但这里建议你上个函数里直接尾插法入链表，这里就是正序，就无需在转换一遍了

	while (s->size != 0)
	{
		char topch = s->top->num;
		pushStack(result, topch);
		// printf("%c", topch);
		popStack(s);
	}

	while (result->size != 0)
	{
		char topch = result->top->num;
		printf("%c", topch);
		popStack(result);
	}
}

int main(void)
{
	char express[80];
	gets_s(express, 80);
	// printf("%s",express);
	Stack s = inToPost(express);
	print(s);
}