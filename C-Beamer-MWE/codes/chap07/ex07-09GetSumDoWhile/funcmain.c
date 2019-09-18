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
