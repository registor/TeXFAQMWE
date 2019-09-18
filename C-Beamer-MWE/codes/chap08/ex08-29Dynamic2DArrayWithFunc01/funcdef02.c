void DestroyArray(int **p, int m)
{
    int i;
    /*释放每一行的空间*/
    for (i = 0; i < m; i++)
    {
        free(p[i]);
        p[i] = NULL; // 赋值为NULL，防止野指针
    }
    /*释放存储每一行首地址的内存空间*/
    free(p);
}
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
