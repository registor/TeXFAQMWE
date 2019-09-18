// 采用插入排序对数组排序
void InsertSort(int *pa, int n, int (*pf)(int, int))
{
    int i, j;
    int temp = 0; // 临时变量

    // 假定第1个元素是有序的，需要进行n-1次插入
    for(i = 1; i < n; i++)
    {
        // 把待排序的元素赋给temp
        temp = pa[i];
        // 初始化j
        j = i - 1;
        // 利用while循环将不符合位置的元素后移一个位置
        while((j >= 0) && pf(temp, pa[j]))
        {
            // 顺序比较和移动
            pa[j + 1] = pa[j];
            j--;
        }
        // 将元素插入空位
        pa[j + 1] = temp;
    }
}
