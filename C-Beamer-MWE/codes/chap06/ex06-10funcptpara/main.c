#include <stdio.h>
#include <stdlib.h>

// 函数原型
int Max(int, int);
int Min(int, int);
int GetVal(int, int, int (*)(int, int));

//主函数
int main()
{
    /*声明变量并初始化*/
    int a = 10, b = 20;
    int c;

    c = GetVal(a, b, Max); /*调用函数*/
    printf("Max=%d\n", c);

    c = GetVal(a, b, Min); /*调用函数*/
    printf("Min=%d\n", c);

    return 0;
}

// 求两个数的最大值
int Max(int x, int y) /*函数头*/
{
    return x > y ? x : y;
}

// 求两个数的最小值
int Min(int x, int y) /*函数头*/
{
    return x < y ? x : y;
}

// 使用函数指针得到最大或最小值
int GetVal(int x, int y, int (*pf)(int, int))
{
    return pf(x, y); /*调用传入的函数*/
}

