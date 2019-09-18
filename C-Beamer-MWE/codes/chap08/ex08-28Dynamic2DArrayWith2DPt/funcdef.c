// 元素赋值
void SetItem(int ** p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        for(j = 0; j  < n; j++)
        {
            // 为数组元素赋值
            p[i][j] = i * j;
        }
    }
}

// 输出函数
void Display(int ** p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        // n-1，不输出最后一个数
        for(j = 0; j  < n - 1; j++)
        {
            // 遍历数组中每一个元素
            printf("%d ", p[i][j]);
        }
        // 最后一个数不输出空格
        printf("%d\n", p[i][j]);
    }
}
