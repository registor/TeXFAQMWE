#include <stdio.h>
#include <stdbool.h>
#define M 3
#define N 2

int main(void)
{
    int i, j;
    int a[M][N]; // 数组声明

    // 整型指针，通过强制类型转换指向数组的起始地址
    int *p = (int *)a;
    int *pTemp; // 整型指针
    int sum1 = 0, sum2 = 0;

    // 数组赋值(双重循环，常规操作)
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            a[i][j] = (i + 1) * (j + 1);
        }
    }

    // 按一维方式操作二维数组(注意偏移量的计算)
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            // 得到第i行，第j列的偏移
            sum1 += *(p + i * N + j);
        }
    }

    // 按一维方式操作二维数组(注意偏移量的计算)
    for(i = 0; i < M; i++)
    {
        pTemp = p + i * N; // 指向第i行的首地址
        for(j = 0; j < N; j++)
        {
            sum2 += *(pTemp + j); // 第j列的偏移
        }
    }

    printf("%d\n", sum1);
    printf("%d\n", sum2);

    return 0;
}
