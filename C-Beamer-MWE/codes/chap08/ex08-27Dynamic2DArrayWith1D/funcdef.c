// 设置数组元素
void SetItem(int * p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        for(j = 0; j  < n; j++)
        {
            // 用一维的方式模拟二维数组
            *(p + i * n + j) = i * j;
        }
    }
}

// 输出函数
void Display(int * p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        // n-1，不输出最后一个数
        for(j = 0; j  < n - 1; j++)
        {
            // 用一维的方式模拟二维数组
            printf("%d ", *(p + i * n + j));
        }
        // 最后一个数不输出空格
        printf("%d\n", *(p + i * n + j));
    }
}
