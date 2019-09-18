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
