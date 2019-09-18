#include <stdio.h>
#include <stdlib.h>

// 函数原型
int isPrime(int);

int main()
{
    int n;

    scanf("%d", &n);

    if(isPrime(n))
    {
        printf("%d is Prime\n", n);
    }
    else
    {
        printf("%d is not Prime\n", n);
    }

    return 0;
}

// 函数定义
int isPrime(int n)
{
    int divisor;

    // 小于1的数不是素数
    if ( n <= 1)
    {
        return 0;
    }

    // 只需要检索到sqrt(n)即可，
    // divisor * divisor <= n是为了避免浮点数运算
    for(divisor = 2; divisor * divisor <= n; divisor++)
    {
        if(n % divisor == 0) // 发现整除则不是素数
        {
            return 0;
        }
    }

    return 1;
}
