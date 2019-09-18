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
