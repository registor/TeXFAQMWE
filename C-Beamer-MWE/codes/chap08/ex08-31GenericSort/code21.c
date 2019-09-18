//--------------------------------------------------------------------------
// 功能：泛型冒泡排序(函数指针用于比较，实现不同数据类型的升/降序)
//            采用了将前一次最后交换位置作为下次循环边界的优化算法，
//            其它优化算法参见：http://www.algorithmist.com/index.php/Bubble_sort
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [int (*comp)(const void*, const void*)] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0。
// 返回：无
//--------------------------------------------------------------------------
void GenericBubbleSort(void *ptr, size_t count, size_t size,
                       int (*comp)(const void*, const void*))
{
    int bound = count - 1, new_bound = 0;

    for(int i = 0; i < count - 1; i++ )
    {
        for(int j = 0; j < bound; j++)
        {
            if(comp(ptr + j * size, ptr + (j + 1) * size) > 0) 
            {
                GenericSwap(ptr + j * size, ptr + (j + 1) * size, size); // 交换
                new_bound = j; // 更新最后一次发生交换的位置
            }
        }
        bound = new_bound; // 更新内层循环上界
    }
}
