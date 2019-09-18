#include <stdio.h>
#include <stdlib.h>
//函数原型, int []表示数组形参
void SetArray(int []);
int main()
{
    int a[3];

    printf("before: %d %d %d\n",
              a[0], a[1], a[2]);
    SetArray(a); // 调用函数
    printf("after: %d %d %d\n",
              a[0], a[1], a[2]);

    return 0;
}
//函数定义
// int p[]表示数组形参名称
void SetArray(int p[])
{
    // p只是一个指针，无法用
    // sizeof(p)得到数组大小
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
}
