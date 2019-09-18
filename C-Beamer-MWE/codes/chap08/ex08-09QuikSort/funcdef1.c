// 递归快速排序
void QuickSort(int *pa, int low, int high, int (*pf)(int, int))
{
    int splitpos; //分割元素位置

    if (low >= high) // 递归结束条件（简单情景）
    {
        return;
    }

    // 分割数组，将分割元素调整到合适的位置
    // 并返回分割元素在数组中的位置
    splitpos = Split(pa, low, high, pf);
    // 对low和splitpos - 1之间的元素递归排序
    QuickSort(pa, low, splitpos - 1, pf);
    // 对splitpos + 1和high之间的元素递归排序
    QuickSort(pa, splitpos + 1, high, pf);
}
