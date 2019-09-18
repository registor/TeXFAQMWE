// 采用冒泡排序对数组排序
int BubbleSortArray(int a[], int n)
{
    int i = 0, j = 0;
    int counter = 0;

    for(i = 0; i < n - 1; i++ )
    {
        // j<n-1确保数据不越界
        // -i为了减少循环次数
        for(j = 0; j < n - 1 - i; j++)
        {
            if(a[j] > a[j + 1]) // 升序
            {
                Swap(&a[j], &a[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}
