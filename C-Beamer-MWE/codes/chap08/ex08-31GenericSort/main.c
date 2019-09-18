/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示采用void指针实现泛型(与类型无关)冒泡排序。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月19日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月19日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 10

//函数原型
void Traversal(void *, size_t, size_t, void (*pf)(void *)); // 数组遍历
// 泛型冒泡排序(函数指针用于比较，以实现升/降序)
void GenericBubbleSort(void *, size_t, size_t, int (*)(const void*, const void*));
void RandIntArray(void *ptr, size_t count, size_t size); // 随机产生一个整数数组
void RandDfArray(void *ptr, size_t count, size_t size); // 随机产生一个浮点数数组
// 功能函数
void InputInt(void *); // 用scanf输入一个整数
void OutputInt(void *); // 用printf输出一个整数
void InputDf(void *);  // 用scanf输入一个浮点数
void OutputDf(void *);  // 用printf输出一个浮点数
// 交换数据(泛型)
void GenericSwap(void *, void *, size_t); // 利用内存拷贝实现
// 比较函数(int型)
int GreaterInt(const void *, const void *); // 比较两个整型数大小(>)
int LesserInt(const void *, const void *); // 比较两个整型数大小(<)
int GreaterDf(const void *, const void *); // 比较两个浮点数大小(>)
int LesserDf(const void *, const void *); // 比较两个浮点数大小(<)

int main()
{
    int iA[N]; // 整型数组

    double dfA[N]; // 浮点型数组

    // 测试整型数组
//    // 把输入重定向到文件"datai.txt"
//    freopen("datai.txt", "r", stdin);
//    Traversal(iA, N, sizeof(iA[0]), InputInt);
//    // 把输入重定向回键盘
//    freopen("CON", "r", stdin);

    // 产生随机数数组
    RandIntArray(iA, N, sizeof(iA[0]));

    // 未排序数组
    Traversal(iA, N, sizeof(iA[0]), OutputInt);
    printf("\n");

    // 升序排序
    GenericBubbleSort(iA, N, sizeof(iA[0]), GreaterInt);
    Traversal(iA, N, sizeof(iA[0]), OutputInt);
    printf("\n");
    // 降序排序
    GenericBubbleSort(iA, N, sizeof(iA[0]), LesserInt);
    Traversal(iA, N, sizeof(iA[0]), OutputInt);
    printf("\n");

    // 测试浮点型数组
//    // 把输入重定向到文件"datadf.txt"
//    freopen("datadf.txt", "r", stdin);
//    Traversal(dfA, N, sizeof(dfA[0]), InputDf);
//    // 把输入重定向回键盘
//    freopen("CON", "r", stdin);

    // 产生随机数数组
    RandDfArray(dfA, N, sizeof(dfA[0]));

    // 未排序数组
    Traversal(dfA, N, sizeof(dfA[0]), OutputDf);
    printf("\n");

    // 升序排序
    GenericBubbleSort(dfA, N, sizeof(dfA[0]), GreaterDf);
    Traversal(dfA, N, sizeof(dfA[0]), OutputDf);
    printf("\n");
    // 降序排序
    GenericBubbleSort(dfA, N, sizeof(dfA[0]), LesserDf);
    Traversal(dfA, N, sizeof(dfA[0]), OutputDf);
    printf("\n");

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void Traversal(void *ptr, size_t count, size_t size, void (*pf)(void *))
// 功能：实现数组的遍历(内在务必要连续)
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
//       [void (*pf)(void *)] --- 处理遍历到的一个元素的函数的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void Traversal(void *ptr, size_t count, size_t size, void (*pf)(void *))
{
    for(int i  = 0; i < count; i++)
    {
        pf(ptr + i * size); // 计算每个元素的地址，传入操作函数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void RandIntArray(void *ptr, size_t count, size_t size)
// 功能：用srand和rand函数产生一个随机整数数组
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void RandIntArray(void *ptr, size_t count, size_t size)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a

    // 置随机种子
    srand(time(NULL));

    for(int i  = 0; i < count; i++)
    {
        *(int*)(ptr + i * size) = rand() % 100; // 生成[0, 100)之间的随机数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void RandDfArray(void *ptr, size_t count, size_t size)
// 功能：用srand和rand函数产生一个随机浮点数数组
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(ptr[0])
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void RandDfArray(void *ptr, size_t count, size_t size)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a

    // 置随机种子
    srand(time(NULL));

    for(int i  = 0; i < count; i++)
    {
        *(double*)(ptr + i * size) =  rand() / (double)(RAND_MAX / 100); // 产生[1,100)内的随机浮点数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void InputInt(void * pData)
// 功能：用scanf输入一个整数
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现整数输入
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void InputInt(void * pData)
{
    scanf("%d", (int*)pData);
}
//-----------------------------------------------------------------------------------------------
// 名称：void OutputInt(void * pData)
// 功能：用printf输出一个整数
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现整数输出
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void OutputInt(void * pData)
{
    // 输出
    printf("%d ", *(int *)pData);
}

//-----------------------------------------------------------------------------------------------
// 名称：void InputDf(void * pData)
// 功能：用scanf输入一个浮点数
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数输入
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void InputDf(void * pData)
{
    scanf("%lf", (double*)pData);
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputDf(void * pData)
// 功能：用printf输出一个浮点数
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数输出
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void OutputDf(void * pData)
{
    // 输出
    printf("%.2f ", *(double *)pData);
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
// 名称：int GreaterInt(const void *a, const void *b)
// 功能：用于整数的比较小于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a > *b返回1，否则返回0
// 注意：需要在函数内部进行强制地址类型转换，以实现整数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int GreaterInt(const void *a, const void *b)
{
    return (*(int*)a > *(int*)b) ? 1 : 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserInt(const void *a, const void *b)
// 功能：用于整数的比较小于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a < *b返回1，否则返回0
// 注意：需要在函数内部进行强制地址类型转换，以实现整数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int LesserInt(const void *a, const void *b)
{
    return (*(int*)b > * (int*)a) ? 1 : 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：int GreaterDf(const void *a, const void *b)
// 功能：用于浮点数的比较大于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a > *b返回1，否则返回0
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int GreaterDf(const void *a, const void *b)
{
    return (*(double*)a > * (double*)b) ? 1 : 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserDf(const void *a, const void *b)
// 功能：用于浮点数的比较小于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a < *b返回1，否则返回0
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int LesserDf(const void *a, const void *b)
{
    return (*(double*)b > * (double*)a) ? 1 : 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void GenericBubbleSort(void *ptr, size_t count, size_t size,
//                                                     int (*comp)(const void*, const void*))
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
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void GenericBubbleSort(void *ptr, size_t count, size_t size,
                       int (*comp)(const void*, const void*))
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
