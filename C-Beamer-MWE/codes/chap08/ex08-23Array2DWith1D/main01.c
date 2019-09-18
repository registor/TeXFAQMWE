#include <stdio.h>
#include <stdbool.h>
#define M 3
#define N 2

int main(void)
{
    int i, j;
    int a[M][N]; // 数组声明

    // 整型指针，通过强制类型转换
    // 指向数组的起始地址
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
