// 递归二分查找
int ReBiSearch(int *pa, int low, int high, int key, int (*pf)(int, int))
{
    // 二分位置
    int mid = -1;

    if(low <= high)
    {
        // 计算二分位置
        mid = (low + high) / 2;
        if(pf(key, pa[mid])) // 小(大)于是间位置，在低半段查找
        {
            // 递归调用
            mid = ReBiSearch(pa, low, mid - 1, key, pf);
        }
        else if(pf(pa[mid], key))// 大(小)于是间位置，在高半段查找
        {
            // 递归调用
            mid = ReBiSearch(pa, mid + 1, high, key, pf);
        }
    }

    return mid;
}
