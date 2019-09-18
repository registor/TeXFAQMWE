// 函数定义
// 交换两个数
void Swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// 为数组输入数据
void InputArray(int a[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}

// 输出数组数据
void OutputArray(int a[], int n)
{
    int i;

    // 暂不输出最后一个数
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", a[i]);
    }

    // 输出最后一个数
    // 避免最后多一个空格
    printf("%d\n", a[i]);
}
