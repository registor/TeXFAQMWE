// 输出数组数据
void OutputArray(int a[], int n)
{
    int i;

    // 遍历数组
    // 暂不输出最后一个数
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", a[i]);
    }

    // 输出最后一个数
    // 避免最后多一个空格
    printf("%d\n", a[i]);
}

// 数组元素清0
void SetArray2Zero(int a[], int n)
{
    int i;

    // 遍历数组
    for(i = 0; i < n; i++)
    {
        a[i] = 0; // 清0
    }
}
