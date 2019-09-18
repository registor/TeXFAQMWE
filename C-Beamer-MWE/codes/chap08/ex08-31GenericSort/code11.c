//-------------------------------------------------------
// 名称：void GenericSwap(void *p1, void *p2, size_t size)
// 功能：实现两个泛型数的交换
// 参数：
//       [void *p1] --- 第一个数起始地址的指针
//       [void *p2] --- 第二个数起始地址的指针
//       [size_t size] --- 数据占有内存的大小(字节)
// 返回：无
// 注意：采用内存拷贝方式实现，需要知道占有的内存大小
// 作者：耿楠
// 日期：2017年11月19日
//-------------------------------------------------------
void GenericSwap(void *p1, void *p2, size_t size)
{
    void *pt = malloc(size); // 分配1个元素大小的内存

    // 清0
    memset(pt, 0, size);

    // 交换内存的内容
    memcpy(pt, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, pt, size);

    // 释放内存
    free(pt);
}
