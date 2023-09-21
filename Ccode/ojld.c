#include<stdio.h>
//  应用辗转相除法，计算出余数
/*  我们将两数中较大的那一个看作是被除数A，
    将较小的那一个看作是除数B，二者相除的商记作C，余数记作D。
    这样我们就可以得到一个等式：A = B×C + D。
    而辗转相除法的所要用到的原理则是：(A , B) = (B , D)，当余数为0时结束算法*/
int Fac(int a, int b)
{
	// 注意定义变量类型
	int d = 1;
	int c = 0;
	while (d)
	{
		c = a / b;
		d = a % b;
		a = b;
		b = d;
	}
	// 注意返回值
	return a;
}

// 主函数
int main()
{
    // 将两个数和答案都初始化将其变为0
	int a = 0;
	int b = 0;
	int ret = 0;
	printf("请输入两个数字：\n");
	scanf("%d %d", &a, &b);
	// 需要注意a，b的大小关系
	if (a>b)
	{
		ret=Fac(a, b);
	}
	else
	{
		ret = Fac(b, a);
	}
	printf("最大公约数：%d\n", ret);
	return 0;
}

