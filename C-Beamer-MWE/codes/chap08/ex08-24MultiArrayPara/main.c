#include <stdio.h>
#include <stdbool.h>
#define M 3
#define N 2

// 第1维长度必须留空，但方括号不能省略
// 第2维必须指明长度
int sum(int a[][N], int);

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

    printf("%d\n", sum(a, M));

    return 0;
}

// 函数定义
// a本质上是一个指向第2维长度是N的
// 二维数组的指针
int sum(int a[][N], int m)
{
    int i, j;
    int sum = 0;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < N; j++)
        {
            sum += a[i][j];
        }
    }

    return sum;
}
