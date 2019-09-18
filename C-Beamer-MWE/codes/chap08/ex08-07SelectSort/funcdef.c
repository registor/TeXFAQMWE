// 函数定义
// 比较两个整数
int Greater(int a, int b)
{
    return (a > b) ? 1 : 0;
}

int Lesser(int a, int b)
{
    return (a < b) ? 1 : 0;
}


// 采用选择排序对数组排序
void SelectionSort(int *pa, int n, int (*pf)(int, int))
{
    int i, j;
    int pos = 0; // 选择的位置

    for(i = 0; i < n - 1; i++)
    {
        pos = i; // 每次将pos置为无序数组的起始位置
        for(j = i + 1; j < n; j++) // 遍历无序数组，找到位置
        {
            // 调用传入的比较函数
            if(pf(pa[pos], pa[j]))
            {
                pos = j; // 更新位置
            }
        }
        // 如果不是无序数组的起始位置，则交换
        if(pos != i)
        {
            // 利用指针操作数组
            Swap(pa + i, pa + pos);
        }
    }
}
