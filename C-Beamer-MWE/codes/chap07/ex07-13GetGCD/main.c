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

// 求两个正整数的最大公约数
int GetGCD(int m, int n)
{
    int r; // 余数

    // 如果m<n，则交换m和n的值
    if(m < n)
    {
        m ^= n;
        n ^= m;
        m ^= n;
    }

    // 辗转相除法
    while(n != 0)
    {
        r = m % n;
        m = n;
        n = r;
    }

    return m;
}
