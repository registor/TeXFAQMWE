// 快速排序中的分割函数
int Split(int *pa, int low, int high, int (*pf)(int, int))
{
    // 把pa[low]复制到分割元素，留出空位
    int part_element = pa[low];

    // 无限循环(通过判断利用break跳出)
    for (;;){
        // 从hight到low，查找小于（大于）分割元素的元素
        while (low < high && pf(part_element, pa[high])){
            high--;
        }
        // 调整结束，退出循环
        if (low >= high){
            break;
        }
        // 将小于（大于）分割元素的元素调整到low位
        // 然后将low + 1
        pa[low++] = pa[high];
        // 从low到hight，查找大于（小于）分割元素的元素
        while (low < high && pf(pa[low], part_element)){
            low++;
        }
        // 调整结束，退出循环
        if (low >= high){
            break;
        }
        // 将大于（小于）分割元素的元素调整到high位
        // 然后将high - 1
        pa[high--] = pa[low];
    }
    // 将分割元素置于找到的位置(空位)
    // 此时左边的所有元素小于(大于)分割元素
    // 右边的所有元素大于(小于)分割元素
    pa[high] = part_element;

    // 返回分割元素的位置
    return high;
}
