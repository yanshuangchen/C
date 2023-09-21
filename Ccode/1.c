# include<stdio.h>
int oj(int a,int b)
{
    int c=0;
    int d=1;
    while(d)
    {
        c = a / b;
        d = a % b;
        a = b;
        b = d;
    }
    return a;
}

int main()
{
    int x=0;int y=0;
    int result = 0;
    scanf("%d %d",&x,&y);
    result = oj(x,y);
    printf("%d和%d的最大公约数为%d",x,y,result);
    return 0;
}