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
