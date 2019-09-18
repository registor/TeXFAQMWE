/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：genericsort.h
* 文件标识：见配置管理计划书
* 摘要：泛型排序的函数原型。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月28日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月28日
------------------------------------------------------------------------------------*/
#ifndef GENERICSORT_H_INCLUDED
#define GENERICSORT_H_INCLUDED

#include <stdlib.h> // size_t的声明

typedef void (*itemFuncType)(void *);
typedef int (*cmpFuncType)(const void*, const void*);

// 数组遍历
void Traversal(void *, size_t, size_t, itemFuncType);

// 泛型排序(函数指针用于比较，以实现升/降序)
void GenericBubbleSort(void *, size_t, size_t, cmpFuncType);
void GenericRecursiveBubbleSort(void *, size_t, size_t, cmpFuncType); // 递归实现
// 泛型选择排序(函数指针用于比较，以实现升/降序)
void GenericSelectSort(void *, size_t, size_t, cmpFuncType);
void GenericRecursiveSelectSort(void *, size_t, size_t, cmpFuncType); // 递归实现
// 泛型插入排序(函数指针用于比较，以实现升/降序)
void GenericInsertSort(void *, size_t, size_t, cmpFuncType);
void GenericRecursiveInsertSort(void *, size_t, size_t, cmpFuncType); // 递归实现
// 泛型快速排序(函数指针用于比较，以实现升/降序)
void GenericIterativeQuickSort(void *, size_t, size_t, cmpFuncType); // 非递归实现
void GenericQuickSortRecursiveByFirst(void *, size_t, size_t, cmpFuncType); // 递归实现，枢轴元素取第1个元素
void GenericQuickSortRecursiveByMedian(void *, size_t, size_t, cmpFuncType); // 递归实现，短数组用插入排序，枢轴初值采用3个数中值
void GenericQuickSortRecursiveByLast(void *, size_t, size_t, cmpFuncType); // 递归实现，枢轴元素取最后一个元素
void GenericQuickSortRecursiveByMiddle(void *, size_t, size_t, cmpFuncType); // 递归实现，枢轴元素取中间值

// 交换数据(泛型)
void GenericSwap(void *, void *, size_t); // 利用内存拷贝实现

#endif // GENERICSORT_H_INCLUDED
