#include <stdio.h>
#include <stdlib.h>

// 求两个数的最大值
int Max(int x, int y) /*函数头*/
{
    int z;  /*内部变量*/

    if(x > y)
    {
        z = x;
    }
    else
    {
        z = y;
    }

    return z; /*返回结果*/
}

//主函数
int main()
{
    int a = 10, b = 20; /*声明变量并初始化*/
    int c;

    c = Max(5, 6); /*函数调用*/
    printf("Max of %d and %d is %d.\n", 5, 6, c);

    c = Max(a, b); /*函数调用*/
    printf("Max of %d and %d is %d.\n", a, b, c);

    c = Max(a + 6, b); /*函数调用*/
    printf("Max of %d and %d is %d.\n", a + 6, b, c);

    c = Max(5 + 6, 7); /*函数调用*/
    printf("Max of %d and %d is %d.\n", 5 + 6, 7, c);

    return 0;
}
