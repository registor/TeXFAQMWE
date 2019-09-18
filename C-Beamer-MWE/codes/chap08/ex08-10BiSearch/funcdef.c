// 二分查找
int BiSearch(int *pa, int n, int key, int (*pf)(int, int))
{
    int low, high, mid;
    int pos = -1;
    low = 0;
    high = n - 1;

    while (low <= high)
    {
        // 中间位置
        mid = (low + high) / 2;
        // 如果key比中间元素小(大)
        if (pf(key, pa[mid]))
        {
            high = mid - 1;//将high置为中间左边第1元素
        }
        // 如果key比中间元素大(小)
        else if (pf(pa[mid], key))
        {
            low = mid + 1;//则将low置为中间右边第1元素
        }
        // 如果x与中间元素相等，即找到了值相等的元素
        else
        {
            pos =  mid;
            break;
        }
    }
    // 返回位置，没有找到则返回 -1 */
    return pos;
}
