#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef;        // 系数
    int expon;       // 指数
    Polynomial link; // 指向下一个结点（项）的指针
};

Polynomial ReadPoly();                         // 读入多项式
void Attach(int c, int e, Polynomial *pRear);  // 将单项插入多项式中
Polynomial Mult(Polynomial P1, Polynomial P2); // 两个多项式相乘
void PrintPoly(Polynomial P);                  // 输出多项式

int main()
{
    Polynomial P1, P2, PP; // 多项式1、多项式2、多项式乘积、多项式和
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    return 0;
}

// 读入多项式
Polynomial ReadPoly()
{
    Polynomial P, Rear, T;
    int c, e, N;
    printf("请输入项数N\n");
    scanf("%d", &N);
    printf("请输入系数和指数，中间以空格分开\n");
    P = (Polynomial)malloc(sizeof(struct PolyNode)); // 链表头空结点
    P->link = NULL;
    Rear = P;
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear); // 将当前项插入多项式尾部
    }
    T = P;
    P = P->link;
    free(T); // 释放头空结点，让P指向第一个结点
    return P;
}

// 将单一节点加入多项式
void Attach(int c, int e, Polynomial *pRear)
{
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P;
    // *pRear的值是Rear的值，改变pRear的值即改变Rear的值，即改变Rear的指向
    *pRear = P; //修改pRear值
}

// 两个多项式相乘
Polynomial Mult(Polynomial P1, Polynomial P2)
{
    Polynomial P, Rear, T1, T2, T; // T用来指向新建的结点，之后用来释放头空结点
    int c, e;
    if (!P1 || !P2)
        return NULL;
    T1 = P1;
    T2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (T2)
    {
        //先用P1的第一项乘以P2,得到P
        Attach(T1->coef * T2->coef, T1->expon + T2->expon, &Rear);
        T2 = T2->link;
    }
    T1 = T1->link;
    while (T1)
    {
        T2 = P2;
        //此时的Rear不是结果链表真正的尾，将其置于头结点
        // Rear是用来查找插入位置的（即指向插入位置前的末尾）
        Rear = P;
        while (T2)
        {
            e = T1->expon + T2->expon;
            c = T1->coef * T2->coef;
            while (Rear->link && Rear->link->expon > e)
                Rear = Rear->link;
            if (Rear->link && Rear->link->expon == e)
            { //指数相等
                if (Rear->link->coef + c)
                    Rear->link->coef += c; // 系数和不为0则相加
                else
                { // 系数为0直接删除（释放掉该结点）
                    T = Rear->link;
                    Rear->link = T->link;
                    free(T);
                }
            }
            else
            {
                T = (Polynomial)malloc(sizeof(struct PolyNode));
                T->coef = c;
                T->expon = e;
                T->link = Rear->link;
                Rear->link = T;
                Rear = Rear->link;
            }
            T2 = T2->link;
        }
        T1 = T1->link;
    }
    // 释放头空结点
    T = P;
    P = P->link;
    free(T);
    return P;
}

// 输出多项式
void PrintPoly(Polynomial P)
{
    int flag = 0; // 辅助调整格式用
    if (!P)
    {
        // 零多项式输出0 0
        printf("0 0\n");
        return;
    }
    // 要求结尾没有多余空格，可以看作没有第一个空格，后面是 空格-单项
    printf("系数和指数分别为\n");

    while (P)
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");

        printf("%d %d\n", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}
