#include <stdio.h>
#include <stdlib.h>

// 函数原型
int GetMax(int, int);

int main()
{
    int iVal1, iVal2;
    int iMax;

    scanf("%d%d", &iVal1, &iVal2);

    // 调用函数
    iMax = GetMax(iVal1, iVal2);

    printf("Max = %d\n", iMax);

    return 0;
}
