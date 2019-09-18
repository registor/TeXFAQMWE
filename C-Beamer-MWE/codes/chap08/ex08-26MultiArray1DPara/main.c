#include <stdio.h>
#include <stdbool.h>
#define M 3
#define N 2

// 用整型指针做形参
// 需要传入数组的长度
int sum(int *, int, int);

int main(void)
{
    int i, j;
    int a[M][N];

    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            a[i][j] = (i + 1) * (j + 1);
        }
    }

    // 需要强制转换
    printf("%d\n", sum((int *)a, M, N));

    return 0;
}

// 函数定义
// pa指向整型数的指针
int sum(int *pa, int m, int n)
{
    int i, j;
    int sum = 0;

    // 按一维方式操作二维数组
    // 注意偏移量的计算
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            // 得到第i行，第j列的偏移
            sum += *(pa + i * n + j);
        }
    }

    return sum;
}
