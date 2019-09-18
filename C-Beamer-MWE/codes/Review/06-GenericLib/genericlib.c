/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：genericsort.c
* 文件标识：见配置管理计划书
* 摘要：泛型排序的函数定义(静态链接库)。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年12月12日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年12月12日
------------------------------------------------------------------------------------*/
#include <string.h>
#include "genericlib.h"

#define QSORTMINLEN 20 // 在递归快速排序中转为插入排序的阈值

//-----------------------------------------------------------------------------------------------
// 名称：void Traversal(void *ptr, size_t count, size_t size, void (*pf)(void *))
// 功能：实现数组的遍历(内存务必要连续)
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(a[0])
//       [void (*pf)(void *)] --- 处理遍历到的一个元素的函数的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void Traversal(void *ptr, size_t count, size_t size, itemFuncType pf)
{
    for(int i  = 0; i < count; i++)
    {
        pf(ptr + i * size); // 计算每个元素的地址，传入操作函数
    }
}

//-----------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------
// 名称：void GenericBubbleSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型冒泡排序(函数指针用于比较，实现不同数据类型的升/降序)
//            采用了将前一次最后交换位置作为下次循环边界的优化算法，
//            其它优化算法参见：http://www.algorithmist.com/index.php/Bubble_sort
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void GenericBubbleSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    int bound = count - 1, new_bound = 0;

    for(int i = 0; i < count - 1; i++ )
    {
        for(int j = 0; j < bound; j++)
        {
            if(comp(ptr + j * size, ptr + (j + 1) * size) > 0) // 比较，前一个数比后一个数大，返回正值
            {
                GenericSwap(ptr + j * size, ptr + (j + 1) * size, size); // 交换
                new_bound = j; // 更新最后一次发生交换的位置
            }
        }
        bound = new_bound; // 更新内层循环上界
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericSelectSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型选择排序(函数指针用于比较，实现不同数据类型的升/降序)
//           算法详情参见：http://www.algorithmist.com/index.php/Bubble_sort
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
void GenericSelectSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    for(int i = 0; i < count; i++ )
    {
        int selpos = i;
        for(int j = i + 1; j < count; j++)
        {
            if(comp(ptr + selpos * size, ptr + j * size) > 0) // 比较
            {
                selpos = j;
            }
        }
        if(selpos != i) // 发现交换元素
        {
            GenericSwap(ptr + i * size, ptr + selpos * size, size); // 交换
        }
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericInsertSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型插入排序(函数指针用于比较，实现不同数据类型的升/降序)
//           算法详情参见：http://www.algorithmist.com/index.php/Bubble_sort
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
void GenericInsertSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    int i = 1;
    int j;

    // 分配用于空出位置的临时空间
    void *p = malloc(size); // 申请一个元素大小(字节)的内存区域

    while(i < count)
    {
        if(comp(ptr + i * size, ptr + (i - 1) * size) < 0) // 条件不成立，则是有序
        {
            memcpy(p, ptr + i * size, size); // 保存当前元素，留出空位
            j = i - 1;
            while (j >= 0 && comp(ptr + j * size, p) > 0) // 找到插入点
            {
                //memcpy(ptr + (j + 1) * size, ptr + j * size, size); // 逐个搬移数据
                j--;
            }
            memmove(ptr + (j + 2) * size, ptr + (j + 1) * size, (i - 1 - j) * size); // 整体搬移数据
            memcpy(ptr + (j + 1) * size, p, size); // 在空位插入保留的最后一个元素
        }
        i++;
    }

    free(p);
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericRecursiveSelSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型冒泡排序(函数指针用于比较，实现不同数据类型的升/降序)
//           采用递归实现。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月21日
//-----------------------------------------------------------------------------------------------
void GenericRecursiveBubbleSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    if(count < 2)
    {
        return;
    }

    for(int i = 0; i < count - 1; i++) // 一趟内的排序
    {
        if(comp(ptr + i * size, ptr + (i + 1) * size) > 0) // 比较
        {
            GenericSwap(ptr + i * size, ptr + (i + 1) * size, size); // 交换
        }
    }
    GenericRecursiveBubbleSort(ptr, count - 1, size, comp); // 递归到下一趟
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericRecursiveSelectSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型选择排序(函数指针用于比较，实现不同数据类型的升/降序)
//           采用递归实现。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月21日
//-----------------------------------------------------------------------------------------------
void GenericRecursiveSelectSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    if(ptr == NULL)   //判断数组是否为空
    {
        return;
    }
    else
    {
        void *p = ptr; // 记录起始地址

        if(count == 1) // count==1表示排序已经完成，递归结束
        {
            return;
        }

        int selIdx = 0; // 假定第0个元素为最小(大)数
        for(int i = 1; i < count; i++) // 查找更小(大)数的位置
        {
            if(comp(p + selIdx * size, p + i * size) > 0) // 比较
            {
                selIdx = i; // 更新最小(大)值的位置
                //GenericSwap(p, p + i * size, size); // 交换
            }
        }

        if(selIdx != 0)
        {
            GenericSwap(p, p + selIdx * size, size); // 交换，将最小(大)数放在最前面
        }

        // 递归排序剩下的数组
        p += size; // 前进1个元素
        count--; // 元素长度减1
        GenericRecursiveSelectSort(p, count, size, comp);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericRecursiveInsertSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型插入排序(函数指针用于比较，实现不同数据类型的升/降序)
//           采用递归实现。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月21日
//-----------------------------------------------------------------------------------------------
void GenericRecursiveInsertSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    // 最简情况，结束递归
    if (count <= 1)
    {
        return;
    }

    // 递归，排序前 n - 1 个元素
    GenericRecursiveInsertSort(ptr, count - 1, size, comp);

    // 将最后一个元素插入到已排序的数组中的合适位置
    void *p = malloc(size); // 申请一个元素大小(字节)的内存区域
    memcpy(p, ptr + (count - 1) * size, size); // 保存最后一个元素
    int j = count - 2;

    // 将ptr[0..i-1]中大(小)于最后一个元素的元素后移一个位置，
    // 以便为插入的元素留出空位
    while (j >= 0 && comp(ptr + j * size, p) > 0)
    {
        //memcpy(ptr + (j + 1) * size, ptr + j * size, size); // 逐个搬移数据
        j--;
    }
    memmove(ptr + (j + 2) * size, ptr + (j + 1) * size, (count - 2 - j) * size); // 整体搬移数据
    memcpy(ptr + (j + 1) * size, p, size); // 在空位插入保留的最后一个元素，注意j已--到位

    free(p); // 释放临时空间
}

//-----------------------------------------------------------------------------------------------
// 名称：static int PartitionByFirst(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序数组分割函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法详情参见：K.N. King 著, 吕秀锋 黄倩译. C语言程序设计:现代方法(第2版), 北京:人民邮电出版社, 2013, PP: 145-147.
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [int low] --- 数组起始索引下标
//       [int high] --- 数组结束索引下标
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：[static int] --- 数组分割位置，左边的小(大)于分割位置的元素，右边反之
// 注意：[static int] --- static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
static int PartitionByFirst(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    // 将low位置的元素备份，留出空位
    void *p = malloc(size); // 申请一个元素大小(字节)的内存区域
    memcpy(p, ptr + low * size, size); // 备份

    // 无限循环(通过判断利用break跳出)
    for (;;)
    {
        // 从hight到low，查找小于（大于）分割元素的元素
        while (low < high && comp(ptr + high * size, p) > 0)
        {
            high--;
        }
        // 调整结束，退出循环
        if (low >= high)
        {
            break;
        }
        // 将小于（大于）分割元素的元素调整到low位
        // 然后将low + 1
        memcpy(ptr + low * size, ptr + high * size, size);
        low++;

        // 从low到hight，查找大于（小于）分割元素的元素
        while (low < high && comp(ptr + low * size, p) < 0)
        {
            low++;
        }
        // 调整结束，退出循环
        if (low >= high)
        {
            break;
        }
        // 将大于（小于）分割元素的元素调整到high位
        // 然后将high - 1
        memcpy(ptr + high * size, ptr + low * size, size);
        high--;
    }

    // 将分割元素置于找到的位置(空位)
    // 此时左边的所有元素小于(大于)分割元素
    // 右边的所有元素大于(小于)分割元素
    memcpy(ptr + high * size, p, size);

    // 释放空间
    free(p);
    // 返回分割元素的位置
    return high;
}

//-----------------------------------------------------------------------------------------------
// 名称：static int PartitionByMedian(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序数组分割函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用第1个、最后1个、中间这3个元素的中值作为枢轴元素。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [int low] --- 数组起始索引下标
//       [int high] --- 数组结束索引下标
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：[static int] --- 数组分割位置，左边的小(大)于分割位置的元素，右边反之
// 注意：[static int] --- static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
static int PartitionByMedian(void *ptr, int low, int high, size_t size,  cmpFuncType comp)
{
    int pivot; // 枢轴元素位置
    int mid = low + (high - low) / 2; // 中间元素位置

    // 找到两个数的大数位置
    pivot = comp(ptr + low * size, ptr + mid * size) > 0 ? low : mid;

    // 找到最小数的位置
    if(comp(ptr + pivot * size, ptr + high * size) > 0)
    {
        pivot = high;
    }

    // 将枢轴元素与第1个元素进行交换
    GenericSwap(ptr + pivot * size, ptr + low * size, size);
    pivot = low; // 起始枢轴位置

    while(low < high)
    {
        //  如果当前(low)元素小(大)于最后元素(high)，则交换枢轴位置与第1个元素，
        //  并将pivot++，否则low++
        if(comp(ptr + low * size, ptr + high * size) <= 0)
        {
            GenericSwap(ptr + pivot * size, ptr + low * size, size); // 交换
            pivot++;
        }
        low++;
    }

    // 交换枢轴(pivot)与最后(high)位置的元素
    // 此时枢轴(pivot)前面的全小(大)于枢轴(pivot)元素，右边则相反
    GenericSwap(ptr + pivot * size, ptr + high * size, size);

    return pivot; // 返回枢轴位置
}

//-----------------------------------------------------------------------------------------------
// 名称：static int PartitionByLast(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序数组分割函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用最后1个作为枢轴元素。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [int low] --- 数组起始索引下标
//       [int high] --- 数组结束索引下标
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：[static int] --- 数组分割位置，左边的小(大)于分割位置的元素，右边反之
// 注意：[static int] --- static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月27日
//-----------------------------------------------------------------------------------------------
static int PartitionByLast(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    void *p = NULL; // 存储枢轴位置上的元素值
    int i = low - 1; // 较小元素的索引

    p = malloc(size); // 申请空间
    memcpy(p, ptr + high * size, size); // 用最后一个元素作为枢轴

    for(int j = low; j <= high - 1; j++)
    {
        // 当前元素小(大)于或等于枢轴元素
        if(comp(p, ptr + j * size) >= 0)
        {
            i++; // 较小元素索引加1
            GenericSwap(ptr + i * size, ptr + j * size, size);
        }
    }
    GenericSwap(ptr + (i + 1) * size, ptr + high * size, size);
    free(p);

    return i + 1; // 返回枢轴位置
}

//-----------------------------------------------------------------------------------------------
// 名称：static int PartitionByMiddle(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序数组分割函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用中间元素作为枢轴元素(Standard Hoare partition scheme)。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [int low] --- 数组起始索引下标
//       [int high] --- 数组结束索引下标
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：[static int] --- 数组分割位置，左边的小(大)于分割位置的元素，右边反之
// 注意：[static int] --- static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月27日
//-----------------------------------------------------------------------------------------------
static int PartitionByMiddle(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    int pivot = low + (high - low) / 2;
    void *p = NULL; // 存储枢轴位置上的元素值

    p = malloc(size); // 申请空间
    memcpy(p, ptr + pivot * size, size); // 用中间元素作为枢轴

    int leftI = low - 1;
    int rightI = high + 1;

    while(leftI <= rightI)
    {
        while(comp(p, ptr + (++leftI) * size) > 0)
        {
            ;
        }
        while(comp(p, ptr + (--rightI) * size) < 0)
        {
            ;
        }
        if(leftI >= rightI)
        {
            break;
        }
        GenericSwap(ptr + leftI * size, ptr + rightI * size, size);
    }

    free(p);
    return rightI;
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericIterativeQuickSort(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：非递归泛型快速排序(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：用栈保存每一个待排序子串的首尾元素下标，下一次while循环时取出这个范围，
//                     对这段子序列进行PartitionByFirst操作。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
void GenericIterativeQuickSort(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    int startIndex = 0; // 首元素下标
    int endIndex = count - 1; // 尾元素下标

    int top = -1; // 栈顶
    int* stack = (int*)malloc(sizeof(int) * count); // 申请栈空间

    stack[++top] = startIndex; // 首元素下标压栈
    stack[++top] = endIndex; // 尾元素下标压栈

    while (top >= 0)
    {
        endIndex = stack[top--]; // 弹出首元素下标
        startIndex = stack[top--]; // 弹出尾元素下标

        int p = PartitionByFirst(ptr, startIndex, endIndex, size, comp); // 查找分割元素位置

        if (p - 1 > startIndex) // 前半段
        {
            stack[++top] = startIndex; // 首元素下标压栈
            stack[++top] = p - 1; // 尾元素下标压栈
        }

        if (p + 1 < endIndex) // 后半段
        {
            stack[++top] = p + 1; // 首元素下标压栈
            stack[++top] = endIndex; // 尾元素下标压栈
        }
    }

    free(stack); // 释放栈空间
}

//-----------------------------------------------------------------------------------------------
// 名称：static void QuickSort(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序递归函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法详情参见：K.N. King 著, 吕秀锋 黄倩译. C语言程序设计:现代方法(第2版), 北京:人民邮电出版社, 2013, PP: 145-147.
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [int low] --- 数组起始索引下标
//       [int high] --- 数组结束索引下标
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：[static void] --- static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
static void QuickSort(void *ptr, int low, int high, size_t size,
                      cmpFuncType comp, // 比较函数
                      int (*partition)(void *, int, int, size_t, cmpFuncType)
                     )
{
    int pivot; // 分割元素位置(枢轴)

    if (low >= high) // 递归结束条件（简单情景）
    {
        return;
    }

    // 分割数组，将分割元素调整到合适的位置
    // 并返回分割元素在数组中的位置
    pivot = partition(ptr, low, high, size, comp);
    // 对low和splitpos - 1之间的元素递归排序
    QuickSort(ptr, low, pivot - 1, size, comp, partition);
    // 对splitpos + 1和high之间的元素递归排序
    QuickSort(ptr, pivot + 1, high, size, comp, partition);
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericQuickSortRecursiveByFirst(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：递归泛型快速排序包装器函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法详情参见：K.N. King 著, 吕秀锋 黄倩译. C语言程序设计:现代方法(第2版), 北京:人民邮电出版社, 2013, PP: 145-147.
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：这只是一个包装器函数，用于为泛型排序函数提供一个统一的接口。
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByFirst(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSort(ptr, 0, count - 1, size, comp, PartitionByFirst); // 调用真正的快速排序函数
}

//-----------------------------------------------------------------------------------------------
// 名称：static void QuickSortTailRecursive(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序递归函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用尾部优化递归，并且当数组长度小于QSORTMINLEN(本例取20)时转入插入排序
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：[static void] --- static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
static void QuickSortTailRecursive(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    while(high - low > QSORTMINLEN)  // 小于给定长度时结束递归
    {
        int pivot; // 分割元素位置(枢轴)

        // 分割数组，将分割元素调整到合适的位置
        // 并返回分割元素在数组中的位置
        pivot = PartitionByMedian(ptr, low, high, size, comp);

        // 根据子数组长度选择合适的递归途径
        if(pivot - low < high - pivot)
        {
            // 对low和pivot - 1之间的元素递归排序
            QuickSortTailRecursive(ptr, low, pivot - 1, size, comp);
            low = pivot + 1;
        }
        else
        {
            // 对pivot + 1和high之间的元素递归排序
            QuickSortTailRecursive(ptr, pivot + 1, high, size, comp);
            high = pivot - 1;
        }
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericQuickSortRecursiveByMedian(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：递归泛型快速排序包装器函数(函数指针用于比较，实现不同数据类型的升/降序)
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：这只是一个包装器函数，用于为泛型排序函数提供一个统一的接口。
// 作者：耿楠
// 日期：2017年11月24日
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByMedian(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSortTailRecursive(ptr, 0, count - 1, size, comp); // 调用优化递归快速排序函数
    GenericInsertSort(ptr, count, size, comp); // 调用插入排序
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericQuickSortRecursiveByLast(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：递归泛型快速排序包装器函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用最后一个元素为枢轴元素
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：这只是一个包装器函数，用于为泛型排序函数提供一个统一的接口。
// 作者：耿楠
// 日期：2017年11月27日
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByLast(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSort(ptr, 0, count - 1, size, comp, PartitionByLast); // 调用真正的快速排序函数
}


//-----------------------------------------------------------------------------------------------
// 名称：static void QuickSortRecursiveByMiddle(void *ptr, int low, int high, size_t size,
//                                                     cmpFuncType comp)
// 功能：泛型快速排序递归函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用中间值做为枢轴元素(Standard Hoare partition scheme)。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [int low] --- 数组起始索引下标
//       [int high] --- 数组结束索引下标
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：[static void] --- static的目的是仅在此文件中使用该函数，
//                                   由于标准算法递归方式与first和last不一致，另外设计一个函数
// 作者：耿楠
// 日期：2017年11月27日
//-----------------------------------------------------------------------------------------------
static void QuickSortRecursiveByMiddle(void *ptr, int low, int high, size_t size, cmpFuncType comp)
{
    int pivot;

    if(low >= high)
    {
        return;
    }

    pivot = PartitionByMiddle(ptr, low, high, size, comp);

    QuickSortRecursiveByMiddle(ptr, low, pivot, size, comp);
    QuickSortRecursiveByMiddle(ptr, pivot + 1, high, size, comp);
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericQuickSortRecursiveByMiddle(void *ptr, size_t count, size_t size,
//                                                     cmpFuncType comp)
// 功能：递归泛型快速排序包装器函数(函数指针用于比较，实现不同数据类型的升/降序)
//           算法：采用中间元素为枢轴元素(Standard Hoare partition scheme)。
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [cmpFuncType comp] --- 比较两个元素大小的函数的函数指针
//                         要求：若前一个比后一个大，返回正值，否则返回0或负值。
// 返回：无
// 注意：这只是一个包装器函数，用于为泛型排序函数提供一个统一的接口。
// 作者：耿楠
// 日期：2017年11月27日
//-----------------------------------------------------------------------------------------------
void GenericQuickSortRecursiveByMiddle(void *ptr, size_t count, size_t size, cmpFuncType comp)
{
    QuickSortRecursiveByMiddle(ptr, 0, count - 1, size, comp); // 调用真正的快速排序函数
}
