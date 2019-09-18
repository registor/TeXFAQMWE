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
