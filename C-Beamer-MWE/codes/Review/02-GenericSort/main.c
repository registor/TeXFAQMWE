/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示采用void指针实现泛型(与类型无关)排序。
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

#define QSORTMINLEN 20
#define N 1000
#define STRLEN 100

// 日期结构体类型
typedef struct
{
    int year;    // 年
    int month;  // 月
    int day;     // 日
} Date;

// 学生结构体类型
typedef struct
{
    int ID;                       // 学号
    char *name;            // 姓名
    char *gender;         // 性别
    Date birthday;  // 生日
} StuNode, *StuNodePt; // typedef重定义新名称

// 类型重定义
typedef void (*itemFuncType)(void *);
typedef int (*cmpFuncType)(const void*, const void*);

/** 泛型排序函数原型 **/
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

/** 遍历操作和比较函数原型 **/
// 产生随机数组
void RandIntArray(void *, size_t, size_t); // 随机产生一个整数数组
void RandDfArray(void *, size_t, size_t); // 随机产生一个浮点数数组
void Rand2DCharArray(void *, size_t, size_t); // 随机产生一个字符串数组(二维字符型数组)
void RandStrPtArray(void *, size_t, size_t, size_t); // 随机产生一个字符串数组(字符型指针数组)

// 数组遍历中操作数组单个元素的功能函数
void InputInt(void *); // 用scanf输入一个整数
void RandInt(void *); // 用随机生成一个整数
void OutputInt(void *); // 用printf输出一个整数
void InputDf(void *);  // 用scanf输入一个浮点数
void RandDf(void *); // 用随机生成一个浮点数
void OutputDf(void *);  // 用printf输出一个浮点数
void InputStr(void *);  // 用scanf输入一个字符串
void OutputStr(void *);  // 用puts输出一个字符串
void OutputStrPt(void *);  // 用puts输出一个字符串
void OutputStu(void *);  // 输出一个结构体内容
void OutputStuPt(void *);  // 输出一个结构体内容

// 排序比较函数
int GreaterInt(const void *, const void *); // 比较两个整型数大小(>)
int LesserInt(const void *, const void *); // 比较两个整型数大小(<)
int GreaterDf(const void *, const void *); // 比较两个浮点数大小(>)
int LesserDf(const void *, const void *); // 比较两个浮点数大小(<)
int GreaterStr(const void *, const void *); // 比较两个字符串大小(>)
int LesserStr(const void *, const void *); // 比较两个字符串大小(<)
int GreaterStrPt(const void *, const void *); // 比较两个字符串(指针数组)大小(>)
int LesserStrPt(const void *, const void *); // 比较两个字符串(指针数组)大小(<)
int GreaterStu(const void *, const void *); // 比较两个结构体大小(>)
int LesserStu(const void *, const void *); // 比较两个结构体大小(<)
int GreaterStuPt(const void *, const void *); // 比较两个结构体大小(>)
int LesserStuPt(const void *, const void *); // 比较两个结构体大小(<)

/** 测试函数原型 **/
void testIntSort(void);
void testDfSort(void);
void testStringSort(void);
void testStringPtSort(void);
void testStuSort(void);
void testStuPtSort(void);

// 排序函数类型重定义
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


int main()
{
    // 置随机种子， 只需要执行1次，不必要在每个函数中都执行
    srand(time(NULL));

    //testIntSort();
    //testDfSort();

    //testStringSort();
    //testStringPtSort();
    testStuSort();

    return 0;
}

/** 测试函数 **/
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


/** 泛型遍历和排序函数 **/
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

/** 产生随机数据函数 **/
//-----------------------------------------------------------------------------------------------
// 名称：void RandIntArray(void *ptr, size_t count, size_t size)
// 功能：用rand函数产生一个随机整数数组
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(a[0])
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void RandIntArray(void *ptr, size_t count, size_t size)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a
    for(int i  = 0; i < count; i++)
    {
        *(int*)(ptr + i * size) = rand() % N; // 生成[0, N)之间的随机数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void RandDfArray(void *ptr, size_t count, size_t size)
// 功能：用rand函数产生一个随机浮点数数组
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)，建议使用sizeof(a[0])
// 返回：无
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
void RandDfArray(void *ptr, size_t count, size_t size)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a
    for(int i  = 0; i < count; i++)
    {
        *(double*)(ptr + i * size) =  rand() / (double)(RAND_MAX / N); // 产生[1,N)内的随机浮点数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：static char *RandString(char *str, size_t size)
// 功能：用rand函数随机产生一个字符串
// 参数：
//       [char *str] --- 字符串起始地址指针
//       [size_t size] --- 字符串长度
// 返回：[static char *] --- 字符串首地址， static的目的是仅在此文件中使用该函数
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
static char *RandString(char *str, size_t size)
{
    // 用于产生随机字符串的字符集(字符只能取该字符集中的字符)
    const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //"0123456789,.-#'?!";
    if(size != 0)
    {
        --size;
        for (size_t n = 0; n < size; n++)
        {
            int key = rand() % (int) (sizeof(charset) - 1); // 随机产生字符集范围内的下标值
            str[n] = charset[key]; // 在字符集中选取字符
        }
        str[size] = '\0'; // 空字符
    }

    return str; // 返回字符串指针
}

//-----------------------------------------------------------------------------------------------
// 名称：void Rand2DCharArray(void *ptr, size_t count, size_t size)
// 功能：随机产生一个字符串数组(字符型二维数组)
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)
// 返回：无
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void Rand2DCharArray(void *ptr, size_t count, size_t size)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a
    for(int i = 0; i < count; i++)
    {
        int strlen = rand() % ((int)size - 2) + 2; // 长度范围：[2, size)

        RandString(ptr, strlen); // 随机产生一个字符串
        ptr += size; // 调整指针
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void RandStrPtArray(void *ptr, size_t count, size_t size)
// 功能：随机产生一个字符串数组(字符型指针数组)
// 参数：
//       [void *ptr] --- 数组起始地址的指针
//       [size_t count] --- 数组长度
//       [size_t size] --- 数组一个元素的大小(字节)
//       [size_t strmaxlen] --- 字符串的最大长度(个)
// 返回：无
// 注意：本函数使用了malloc函数，调用后注意使用free函数释放空间
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void RandStrPtArray(void *ptr, size_t count, size_t size, size_t strmaxlen)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a

    char *p ;

    for(int i = 0; i < count; i++)
    {
        int strlen = rand() % (strmaxlen - 2) + 2; // 长度范围：[2, strmaxlen)

        p = (char*)malloc(strlen * sizeof(char)); // 分配空间
        RandString(p, strlen); // 随机产生一个字符串
        memcpy(ptr, &p, size);
        ptr += size; // 调整指针
    }
}

/** 遍历中使用的输入输出函数 **/
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
// 名称：void RandInt(void * pData)
// 功能：用rand函数产生一个随机整数
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现整数输入
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void RandInt(void * pData)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a
    *(int*)(pData) = rand() % N; // 生成[0, N)之间的随机数
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
// 名称：void RandDf(void * pData)
// 功能：用rand函数产生一个随机浮点数
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数输入
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void RandDf(void * pData)
{
    // 要取[a,b)之间的随机整数（包括a，但不包括b)，使用：
    // (rand() % (b - a)) + a
    *(double*)(pData) =  rand() / (double)(RAND_MAX / N); // 产生[1,N)内的随机浮点数
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
// 名称：void InputStr(void * pData)
// 功能：用scanf输入一个字符串
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串输入
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void InputStr(void * pData)
{
    scanf(" %[^\n]", (char *)pData); // 前导空格用于丢弃前一次scanf留下的'\n'，"%[^\n]"用于匹配除\n外的所有字符
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputStr(void * pData)
// 功能：用puts输出一个字符串
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以字符串输出
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void OutputStr(void * pData)
{
    // 输出
    puts((char *)pData);
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputStrPt(void * pData)
// 功能：用puts输出一个字符串
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以字符串输出
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
void OutputStrPt(void * pData)
{
    // 输出
    puts(*(char **)pData);
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputStu(void * pData)
// 功能：输出一个结构体的内容
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以结构体形式输出
// 作者：耿楠
// 日期：2017年11月29日
//-----------------------------------------------------------------------------------------------
void OutputStu(void * pData)
{
    // 强制转换指针类型
    StuNode *p = (StuNode *)pData;
    // 输出
    printf("%d\t%s\t%s\t%d/%d/%d\n", p->ID, p->name,
           p->gender, p->birthday.year,
           p->birthday.month, p->birthday.day);
}

//-----------------------------------------------------------------------------------------------
// 名称：void OutputStuPt(void * pData)
// 功能：输出一个结构体的内容
// 参数：
//       [void * pData] --- 数据起始地址的指针
// 返回：无
// 注意：需要在函数内部进行强制地址类型转换，以结构体形式输出
// 作者：耿楠
// 日期：2017年11月30日
//-----------------------------------------------------------------------------------------------
void OutputStuPt(void * pData)
{
    // 强制转换指针类型
    StuNode *p = *((StuNode **)pData);
    // 输出
    printf("%d\t%s\t%s\t%d/%d/%d\n", p->ID, p->name,
           p->gender, p->birthday.year,
           p->birthday.month, p->birthday.day);
}

/** 泛型排序中的比较函数 **/
//-----------------------------------------------------------------------------------------------
// 名称：int GreaterInt(const void *a, const void *b)
// 功能：用于整数的比较小于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a > *b返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现整数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int GreaterInt(const void *a, const void *b)
{
    // a > b = 1, a < b = -1, (a == b) = 0
    // (*a > *b) - (*a < *b);
    return (*(const int*)a > *(const int*)b) - (*(const int*)a < * (const int*)b);
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserInt(const void *a, const void *b)
// 功能：用于整数的比较小于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a < *b返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现整数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int LesserInt(const void *a, const void *b)
{
    //return *(const int*)b - * (const int*)a;
    return (*(const int*)b > *(const int*)a) - (*(const int*)b < * (const int*)a);
}

//-----------------------------------------------------------------------------------------------
// 名称：int GreaterDf(const void *a, const void *b)
// 功能：用于浮点数的比较大于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a > *b返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int GreaterDf(const void *a, const void *b)
{
    return (*(const double*)a > *(const double*)b) ? 1 :
           (*(const double*)a < * (const double*)b) ? -1 : 0;//*(double*)a - * (double*)b;
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserDf(const void *a, const void *b)
// 功能：用于浮点数的比较小于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a < *b返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数比较
// 作者：耿楠
// 日期：2017年11月19日
//-----------------------------------------------------------------------------------------------
int LesserDf(const void *a, const void *b)
{
    return (*(const double*)b > *(const double*)a) ? 1 :
           (*(const double*)b < * (const double*)a) ? -1 : 0; //*(double*)b - * (double*)a;
}

//-----------------------------------------------------------------------------------------------
// 名称：int GreaterStr(const void *s1, const void *s2)
// 功能：用于浮点数的比较大于函数(二维数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- *s1 > *s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
int GreaterStr(const void *s1, const void *s2)
{
    return (strcmp((const char *)s1, (const char *)s2));
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserStr(const void *s1, const void *s2)
// 功能：用于字符串比较小于的函数(二维数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- *s1< *s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
int LesserStr(const void *s1, const void *s2)
{
    return (strcmp((const char *)s2, (const char *)s1));
}

//-----------------------------------------------------------------------------------------------
// 名称：int GreaterStrPt(const void *s1, const void *s2)
// 功能：用于字符串比较大于的函数(指针数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- **s1 > **s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
int GreaterStrPt(const void *s1, const void *s2)
{
    return (strcmp(*(const char **)s1, *(const char **)s2));
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserStrPt(const void *s1, const void *s2)
// 功能：用于字符串比较小于的函数(指针数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- **s1 < **s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月23日
//-----------------------------------------------------------------------------------------------
int LesserStrPt(const void *s1, const void *s2)
{
    return (strcmp(*(const char **)s2, *(const char **)s1));
}

//-----------------------------------------------------------------------------------------------
// 名称：int GreaterStu(const void *s1, const void *s2)
// 功能：用于字符串比较大于的函数(指针数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- **s1 > **s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月29日
//-----------------------------------------------------------------------------------------------
int GreaterStu(const void *s1, const void *s2)
{
    StuNodePt p1 = (StuNodePt)s1;
    StuNodePt p2 = (StuNodePt)s2;
    return (strcmp(p1->name, p2->name));//p1->ID - p2->ID;
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserStu(const void *s1, const void *s2)
// 功能：用于字符串比较小于的函数(指针数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- **s1 < **s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月29日
//-----------------------------------------------------------------------------------------------
int LesserStu(const void *s1, const void *s2)
{
    StuNodePt p1 = (StuNodePt)s1;
    StuNodePt p2 = (StuNodePt)s2;
    return (strcmp(p2->name, p1->name));//p2->ID - p1->ID;
}

//-----------------------------------------------------------------------------------------------
// 名称：int GreaterStuPt(const void *s1, const void *s2)
// 功能：用于字符串比较大于的函数(指针数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- **s1 > **s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月30日
//-----------------------------------------------------------------------------------------------
int GreaterStuPt(const void *s1, const void *s2)
{
    StuNodePt p1 = *((StuNodePt *)s1);
    StuNodePt p2 = *((StuNodePt *)s2);
    return (strcmp(p1->name, p2->name));//p1->ID - p2->ID;
}

//-----------------------------------------------------------------------------------------------
// 名称：int LesserStuPt(const void *s1, const void *s2)
// 功能：用于字符串比较小于的函数(指针数组方式)
// 参数：
//       [const void *s1] --- 第一个元素的起始地址
//       [const void *s2] --- 第二个元素的起始地址
// 返回：[int] --- **s1 < **s2返回正值，否则返回0或负值
// 注意：需要在函数内部进行强制地址类型转换，以实现字符串比较
// 作者：耿楠
// 日期：2017年11月30日
//-----------------------------------------------------------------------------------------------
int LesserStuPt(const void *s1, const void *s2)
{
    StuNodePt p1 = *((StuNodePt *)s1);
    StuNodePt p2 = *((StuNodePt *)s2);
    return (strcmp(p2->name, p1->name));//p2->ID - p1->ID;
}
