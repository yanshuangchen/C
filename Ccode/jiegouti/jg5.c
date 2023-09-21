#include <stdio.h>

struct Person {
    char name[20];
    int age;
    float height;
};

int main() 
{
    struct Person person;
    printf("结构体 Person 大小为: %zu 字节\n", sizeof(person));
    return 0;
}