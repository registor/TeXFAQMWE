#include <stdio.h>
#include <stdbool.h>
#define M 3
#define N 2

// 数组地址类型的指针做形参
// 方括及长度不可省略
int sum(int (*)[N], int);

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
// pa指向第2维长度是N的2维数组的指针
int sum(int (*pa)[N], int m)
{
    int i, j;
    int sum = 0;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < N; j++)
        {
            sum += pa[i][j];
        }
    }

    return sum;
}
