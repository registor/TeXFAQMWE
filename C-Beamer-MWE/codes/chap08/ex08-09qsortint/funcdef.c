// 比较函数
int cmp(const void *a, const void *b)
{
    // 先转换为(int*)，再用*(int*)取内容
    // 不安全 
    return (*(int *)a - * (int *)b);
}
// 采用随机函数创建数组
void CreateArray(int *pa, int n)
{
    int i;
    // 用时间做随机种子，产生不同随机数
    srand((unsigned)time(NULL));
    for (i = 0; i < n; i++)
    {
        // 产生[0, n)之间的随机数
        pa[i] = rand() % n;
    }
}
// 输出数据
void Output(int * pData, int n)
{
    int i;
    // n - 1不输出最后一个数
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", pData[i]);
    }
    // 最后不输出空格，并输出\n
    printf("%d\n", pData[i]);
}
