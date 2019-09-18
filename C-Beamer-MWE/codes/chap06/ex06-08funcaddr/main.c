#include <stdio.h>
#include <stdlib.h>

// 求两个数的最大值
int Max(int x, int y) /*函数头*/
{
    return x > y ? x : y;
}

//主函数
int main()
{
    /*声明变量并初始化*/
    int a = 10, b = 20;
    int c;

    c = Max(a, b); /*函数调用*/
    printf("Max of %d and %d is %d.\n",
              a, b, c);

    return 0;
}
