/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：genericsort.h
* 文件标识：见配置管理计划书
* 摘要：泛型排序的函数原型(动态链接库)。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年12月12日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年12月12日
------------------------------------------------------------------------------------*/
#ifndef GENERICSORT_H_INCLUDED
#define GENERICSORT_H_INCLUDED

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h> // size_t的声明

typedef void (*itemFuncType)(void *);
typedef int (*cmpFuncType)(const void*, const void*);

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
void DLL_EXPORT Traversal(void *, size_t, size_t, itemFuncType);

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
void DLL_EXPORT GenericBubbleSort(void *, size_t, size_t, cmpFuncType);

//-----------------------------------------------------------------------------------------------
// 名称：void GenericRecursiveBubbleSort(void *ptr, size_t count, size_t size,
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
void DLL_EXPORT GenericRecursiveBubbleSort(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericSelectSort(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericRecursiveSelectSort(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericInsertSort(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericRecursiveInsertSort(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericIterativeQuickSort(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericQuickSortRecursiveByFirst(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericQuickSortRecursiveByMedian(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericQuickSortRecursiveByLast(void *, size_t, size_t, cmpFuncType);

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
void DLL_EXPORT GenericQuickSortRecursiveByMiddle(void *, size_t, size_t, cmpFuncType);

#ifdef __cplusplus
}
#endif

#endif // GENERICSORT_H_INCLUDED
