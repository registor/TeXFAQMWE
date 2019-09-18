#include <stdio.h>
#include <stdlib.h>

// 函数原型
int GetSum(int);

int main()
{
    int n;

    // 输入数据
    scanf("%d", &n);

    // 调用函数
    printf("Sum = %d\n", GetSum(n));

    return 0;
}

// 函数定义
int GetSum(int n)
{
    int i = 0; // 循环变量
    int sum = 0; // 累加器

    while(i < n)
    {
        sum += (i + 1); // 注意i + 1
        i++; //改变循环变量
    }

    return sum;
}
