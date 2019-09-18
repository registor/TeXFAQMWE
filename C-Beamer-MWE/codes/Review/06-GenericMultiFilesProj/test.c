/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：test.c
* 文件标识：见配置管理计划书
* 摘要：测试函数的函数定义。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月28日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月28日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <genericlib.h>

#include "callback.h"
#include "test.h"
#include "define.h"

typedef void(*sortFuncType)(void *, size_t, size_t, int (*)(const void*, const void*));


// 排序函数指针数组
sortFuncType pfSort[] =
{
    GenericBubbleSort,                 // 冒泡排序函数
    GenericRecursiveBubbleSort,   // 递归冒泡排序函数
    GenericSelectSort,                   // 选择排序
    GenericRecursiveSelectSort,    //  递归选择排序函数
    GenericInsertSort,                    // 插入排序
    GenericRecursiveInsertSort,     // 递归插入排序函数
    GenericIterativeQuickSort,       // 迭代快速排序函数
    GenericQuickSortRecursiveByFirst,    // 递归快速排序函数，第1个元素为枢轴元素
    GenericQuickSortRecursiveByMedian,                   // 递归结合插入快速排序函数，第1个，最后一个，中间3个元素的中值为枢轴元素
    GenericQuickSortRecursiveByLast, // 递归快速排序， 最后一个元素为枢轴元素
    GenericQuickSortRecursiveByMiddle, // 递归快速排序， 中间值为枢轴元素
    NULL
};

// 排序函数名称指针数组(字符串指针)
char *pfSortName[] =
{
    "BUBBLE:",                  // 冒泡排序
    "RECURSIVE BUBBLE:",   // 递归冒泡排序
    "SELECT:",                    // 选择排序
    "RECURSIVE SELECT:",     //  递归选择排序
    "INSERT:",                     //  递归选择排序
    "RECURSIVE INSERT:",      // 递归插入排序
    "ITERATIVE QUICK SORT:",   // 迭代快速排序
    "RECURSIVE QUICK SORT BY FIRST:", // 递归快速排序
    "QUICK SORT INERT MEDIAN-3:",       // 递归结合插入快速排序
    "RECURSIVE QUICK SORT BY LAST:",       // 递归快速排序
    "RECURSIVE QUICK SORT BY MIDDLE:",       // 递归快速排序
    NULL
};

// 排序函数名称指针数组(字符串指针)
char *pfCompName[] =
{
    "Ascending",   //  升序
    "Descending",   // 降序
    NULL
};

// 测试函数
void testIntSort(void)
{
    // 整型数比较函数指针数组
    cmpFuncType pfComp[] =
    {
        GreaterInt, // 整型比较函数(>)
        LesserInt,   // 整型比较函数(<)
        NULL
    };

    int iA[N]; // 整型数组
    int iB[N]; // 整型数组
    int iC[N]; // 整型数组

    int count = sizeof(iA) / sizeof(iA[0]); // 数组长度(个)
    int size = sizeof(iA[0]); // 数组单元长度(字节)

    // 产生随机数数组
    RandIntArray(iA, count, size);
    memcpy(iB, iA, count * size); // 备份
    memcpy(iC, iA, count * size); // 备份

    int i = 0;

    // 用于测试函数调用消耗的时间
    clock_t start, stop; //clock_t是clock()函数返回的变量类型
    double duration;

    while(pfSort[i] != NULL)
    {
        int j = 0;
        printf("\n");
        puts(pfSortName[i]);
        while(pfComp[j] != NULL)
        {
            start = clock();
            pfSort[i](iA, count, size, pfComp[j]);
            stop = clock();
            //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s sort execution time: %lf s\n", pfCompName[j], duration);

            start = clock();
            qsort(iC, count, size, pfComp[j]);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s C Lib qsort() execution time: %lf s\n", pfCompName[j], duration);

            // 与qsort()函数的排序结果进行比较，验证代码正确性
            if(memcmp(iA, iC, count * size) == 0)
            {
                printf("Result same with C Lib qsort(), OK!\n");
            }
            else
            {
                printf("Result Don't same with C Lib qsort(), NO!\n");
            }
            memcpy(iA, iB, count * size); // 恢复数据
            memcpy(iC, iB, count * size); // 恢复数据
            printf("\n");
            j++;
        }
        i++;
    }
}

void testDfSort(void)
{
    // 浮点数比较函数指针数组
    cmpFuncType pfComp[] =
    {
        GreaterDf, // 浮点比较函数(>)
        LesserDf,   // 浮点比较函数(<)
        NULL
    };

    double dfA[N]; // 浮点数组
    double dfB[N]; // 浮点数组
    double dfC[N]; // 浮点数组

    int count = sizeof(dfA) / sizeof(dfA[0]); // 数组长度(个)
    int size = sizeof(dfA[0]); // 数组单元长度(字节)

    // 产生随机数数组
    Traversal(dfA, count, size, RandDf);
    memcpy(dfB, dfA, count * size); // 备份
    memcpy(dfC, dfA, count * size); // 备份

    int i = 0;

    // 用于测试函数调用消耗的时间
    clock_t start, stop; //clock_t是clock()函数返回的变量类型
    double duration;

    while(pfSort[i] != NULL)
    {
        int j = 0;
        printf("\n");
        puts(pfSortName[i]);
        while(pfComp[j] != NULL)
        {
            start = clock();
            pfSort[i](dfA, count, size, pfComp[j]);
            stop = clock();
            //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s sort execution time: %lf s\n", pfCompName[j], duration);

            start = clock();
            qsort(dfC, count, size, pfComp[j]);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s C Lib qsort() execution time: %lf s\n", pfCompName[j], duration);

            // 与qsort()函数的排序结果进行比较，验证代码正确性
            if(memcmp(dfA, dfC, count * size) == 0)
            {
                printf("Result same with C Lib qsort(), OK!\n");
            }
            else
            {
                printf("Result Don't same with C Lib qsort(), NO!\n");
            }
            memcpy(dfA, dfB, count * size); // 恢复数据
            memcpy(dfC, dfB, count * size); // 恢复数据
            printf("\n");
            j++;
        }
        i++;
    }
}

void testStringSort(void)
{
//    char planets[][8] = {"Mercury", "Venus", "Earth", "Mars",
//                         "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"
//                        };
//    int count = sizeof(planets) / sizeof(planets[0]); // 数组长度(个)
//    int size = sizeof(planets[0]) / sizeof(planets[0][0]); // 数组单元长度(字节)

    // 字符串比较函数指针数组
    cmpFuncType pfComp[] =
    {
        GreaterStr, // 字符串比较函数(>)
        LesserStr,   // 字符串比较函数(<)
        NULL
    };

    char chA[N][STRLEN]; // 字符串数组
    char chB[N][STRLEN]; // 字符串数组
    char chC[N][STRLEN]; // 字符串数组

    int count = sizeof(chA) / sizeof(chA[0]); // 数组长度(个)
    int size = sizeof(chA[0]) / sizeof(chA[0][0]); // 数组单元长度(字节)

    // 产生随机数数组
    Rand2DCharArray(chA, count, size);
    memcpy(chB, chA, count * size); // 备份
    memcpy(chC, chA, count * size); // 备份

    int i = 0;

    // 用于测试函数调用消耗的时间
    clock_t start, stop; //clock_t是clock()函数返回的变量类型
    double duration;

    while(pfSort[i] != NULL)
    {
        int j = 0;
        printf("\n");
        puts(pfSortName[i]);
        while(pfComp[j] != NULL)
        {
            start = clock();
            pfSort[i](chA, count, size, pfComp[j]);
            stop = clock();
            //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s sort execution time: %lf s\n", pfCompName[j], duration);

            start = clock();
            qsort(chC, count, size, pfComp[j]);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s C Lib qsort() execution time: %lf s\n", pfCompName[j], duration);

            // 与qsort()函数的排序结果进行比较，验证代码正确性
            if(memcmp(chA, chC, count * size) == 0)
            {
                printf("Result same with C Lib qsort(), OK!\n");
            }
            else
            {
                printf("Result Don't same with C Lib qsort(), NO!\n");
            }
            memcpy(chA, chB, count * size); // 恢复数据
            memcpy(chC, chB, count * size); // 恢复数据
            printf("\n");
            j++;
        }
        i++;
    }
}

void testStringPtSort(void)
{
//    //char *str[10] = {NULL}; // 定义一个字符型指针数组，并初始化为NULL
//    char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter",
//                       "Saturn", "Uranus", "Neptune", "Pluto"
//                      };
//    int count = sizeof(planets) / sizeof(planets[0]); // 数组长度(个)
//    int size = sizeof(planets[0]); // 数组单元长度(字节)

    // 字符串指针数组比较函数指针数组
    cmpFuncType pfComp[] =
    {
        GreaterStrPt, // 字符串指针数组比较函数(>)
        LesserStrPt,   // 字符串指针数组比较函数(<)
        NULL
    };

    char *strPtA[N]; // 字符串数组指针
    char *strPtB[N]; // 字符串数组指针
    char *strPtC[N]; // 字符串数组指针

    int count = sizeof(strPtA) / sizeof(strPtA[0]); // 数组指针长度(个)
    int size = sizeof(strPtA[0]); // 数组指针单元长度(字节)

    RandStrPtArray(strPtA, count, size, STRLEN); // 随机生成字符串数组(指针数组)

    memcpy(strPtB, strPtA, count * size); // 备份
    memcpy(strPtC, strPtA, count * size); // 备份

    int i = 0;

    // 用于测试函数调用消耗的时间
    clock_t start, stop; //clock_t是clock()函数返回的变量类型
    double duration;

    while(pfSort[i] != NULL)
    {
        int j = 0;
        printf("\n");
        puts(pfSortName[i]);
        while(pfComp[j] != NULL)
        {
            start = clock();
            pfSort[i](strPtA, count, size, pfComp[j]);
            stop = clock();
            //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s sort execution time: %lf s\n", pfCompName[j], duration);

            start = clock();
            qsort(strPtC, count, size, pfComp[j]);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s C Lib qsort() execution time: %lf s\n", pfCompName[j], duration);

            // 与qsort()函数的排序结果进行比较，验证代码正确性
            if(memcmp(strPtA, strPtC, count * size) == 0)
            {
                printf("Result same with C Lib qsort(), OK!\n");
            }
            else
            {
                printf("Result Don't same with C Lib qsort(), NO!\n");
            }
            memcpy(strPtA, strPtB, count * size); // 恢复数据
            memcpy(strPtC, strPtB, count * size); // 恢复数据
            printf("\n");
            j++;
        }
        i++;
    }

    for(int i = 0; i < count; i++)
    {
        free(strPtA[i]); // 释放内存
    }
}

void testStuSort(void)
{
    // 结构体比较函数指针数组
    cmpFuncType pfComp[] =
    {
        GreaterStu, // 结构体比较函数(>)
        LesserStu,   // 结构体比较函数(<)
        NULL
    };

    // 创建数组，注意name和gender指向字符串常量，不可更改
    StuNode StuA[5] = {{101, "zhang", "male", {1998, 10, 23}},
        {102, "wang", "male", {1999, 1, 2}},
        {103, "li", "female", {2000, 11, 12}},
        {104, "zhao", "male", {1997, 7, 10}},
        {105, "xie", "female", {2001, 9, 10}}
    };
    StuNode StuB[5]; // 结构体数组
    StuNode StuC[5]; // 结构体数组

    int count = sizeof(StuA) / sizeof(StuA[0]); // 数组指针长度(个)
    int size = sizeof(StuA[0]); // 数组指针单元长度(字节)

    memcpy(StuB, StuA, count * size); // 备份
    memcpy(StuC, StuA, count * size); // 备份

    Traversal(StuA, count, size, OutputStu);
//    Traversal(StuB, count, size, OutputStu);
//    Traversal(StuC, count, size, OutputStu);



    int i = 0;

    // 用于测试函数调用消耗的时间
    clock_t start, stop; //clock_t是clock()函数返回的变量类型
    double duration;

    while(pfSort[i] != NULL)
    {
        int j = 0;
        printf("\n");
        puts(pfSortName[i]);
        while(pfComp[j] != NULL)
        {
            start = clock();
            pfSort[i](StuA, count, size, pfComp[j]);
            stop = clock();
            Traversal(StuA, count, size, OutputStu);
            //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s sort execution time: %lf s\n", pfCompName[j], duration);

            start = clock();
            qsort(StuC, count, size, pfComp[j]);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s C Lib qsort() execution time: %lf s\n", pfCompName[j], duration);

            // 与qsort()函数的排序结果进行比较，验证代码正确性
            if(memcmp(StuA, StuC, count * size) == 0)
            {
                printf("Result same with C Lib qsort(), OK!\n");
            }
            else
            {
                printf("Result Don't same with C Lib qsort(), NO!\n");
            }
            memcpy(StuA, StuB, count * size); // 恢复数据
            memcpy(StuC, StuB, count * size); // 恢复数据
            printf("\n");
            j++;
        }
        i++;
    }
}

void testStuPtSort(void)
{
    // 结构体比较函数指针数组
    cmpFuncType pfComp[] =
    {
        GreaterStuPt, // 结构体比较函数(>)
        LesserStuPt,   // 结构体比较函数(<)
        NULL
    };

    // 使用复合字面量创建数组(C99)，注意name和gender指向字符串常量，不可更改
    StuNodePt StuA[5] = {
        &(StuNode){101, "zhang", "male", {1998, 10, 23}},
        &(StuNode){102, "wang", "male", {1999, 1, 2}},
        &(StuNode){103, "li", "female", {2000, 11, 12}},
        &(StuNode){104, "zhao", "male", {1997, 7, 10}},
        &(StuNode){105, "xie", "female", {2001, 9, 10}}
    };
    StuNodePt StuB[5]; // 结构体数组
    StuNodePt StuC[5]; // 结构体数组

    int count = sizeof(StuA) / sizeof(StuA[0]); // 数组指针长度(个)
    int size = sizeof(StuA[0]); // 数组指针单元长度(字节)

    memcpy(StuB, StuA, count * size); // 备份
    memcpy(StuC, StuA, count * size); // 备份

    Traversal(StuA, count, size, OutputStuPt);
//    Traversal(StuB, count, size, OutputStu);
//    Traversal(StuC, count, size, OutputStu);



    int i = 0;

    // 用于测试函数调用消耗的时间
    clock_t start, stop; //clock_t是clock()函数返回的变量类型
    double duration;

    while(pfSort[i] != NULL)
    {
        int j = 0;
        printf("\n");
        puts(pfSortName[i]);
        while(pfComp[j] != NULL)
        {
            start = clock();
            pfSort[i](StuA, count, size, pfComp[j]);
            stop = clock();
            Traversal(StuA, count, size, OutputStuPt);
            //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s sort execution time: %lf s\n", pfCompName[j], duration);

            start = clock();
            qsort(StuC, count, size, pfComp[j]);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("%s C Lib qsort() execution time: %lf s\n", pfCompName[j], duration);

            // 与qsort()函数的排序结果进行比较，验证代码正确性
            if(memcmp(StuA, StuC, count * size) == 0)
            {
                printf("Result same with C Lib qsort(), OK!\n");
            }
            else
            {
                printf("Result Don't same with C Lib qsort(), NO!\n");
            }
            memcpy(StuA, StuB, count * size); // 恢复数据
            memcpy(StuC, StuB, count * size); // 恢复数据
            printf("\n");
            j++;
        }
        i++;
    }
}
