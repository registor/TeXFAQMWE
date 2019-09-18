#include <stdio.h>
#include <stdlib.h>

// 函数原型
int GetGCD(int, int);

int main( void )
{
    int iVal1, iVal2; // 2个正整数
    int result; // 最大公约数

    scanf("%d%d", &iVal1, &iVal2);

    result = GetGCD(iVal1, iVal2);

    // 输出结果
    printf("%d\n", result);

    return 0;
}
