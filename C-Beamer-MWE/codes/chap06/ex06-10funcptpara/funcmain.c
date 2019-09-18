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
