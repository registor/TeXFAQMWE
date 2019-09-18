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
