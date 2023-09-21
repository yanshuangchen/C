#include<stdio.h>
#include<stdlib.h>

typedef struct student
{
    char name[100];
    int age;
    struct student *next; //也可以规范一点写成struct student *next 
}student;

int main(void)
{
    student stu1={"hjw",18};
    student *p = &stu1;
    printf("%s,%d\n",p->name,p->age);
    p->age=19;
    printf("%d\n",p->age);
    return 0; 
}