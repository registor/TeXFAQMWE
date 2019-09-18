// 函数定义
// pa是指向第2维长度是N的2维数组指针
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
