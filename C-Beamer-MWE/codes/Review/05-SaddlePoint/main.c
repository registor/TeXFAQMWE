/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示二维数组的一维方式、数组指针方式作函数形参的操作。
*           以求一个矩阵(二维数组)的鞍点为例，一个矩阵的鞍点是指：
*           鞍点位置上的元素在该行上最大，在该列上最小。
* 基本思想：
*            按行扫描矩阵，提取出当前i行作为一个一维数组，找到其
*            最大值位置nMaxColPos，再提取出nMaxColPos列的数据
*            作为一个一维数组，找到其最小值位置nMinRowPos。若
*            nMinRowPos等当前行i，则是一个鞍点。
*            另外，一个矩阵可以有多个鞍点
*            本程序演示了用一级指针(一维方式访问二维数组)和用数组指针
*            两种函数形参模式，并使用了C99的变长数组作为函数形参。
* 当前版本：2.0
* 作者：耿楠
* 完成日期：2017年11月22日
*
* 取代版本：1.0
* 原作者：耿楠
* 完成日期：2010年12月16日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数原型
void Input1D(int *, int, int); // 输入数据(1维方式)
void Output1D(int *, int, int); // 输出数据(1维方式)
void Input2D(int m, int n, int (*)[n] ); // 输入数据(数组指针，2维方式)
void Output2D(int m, int n, int (*)[n]); // 输出数据(数组指针，2维方式)

int GetMaxPos(int *, int); // 获取一个数组中最大数的位置
int GetMinPos(int *, int); // 获取一个数组中最小数的位置

void GetOneRow1D(int *, int *, int, int); // 获取二维数组的一行数据(1维方式)
void GetOneRow2D(int n, int (*)[n], int *, int); // 获取二维数组的一行数据(数组指针，2维方式)

void GetOneCol1D(int *, int *, int, int, int); // 获取二维数组的一行数据(1维方式)
void GetOneCol2D(int m, int n, int (*)[n], int *, int); // 获取二维数组的一行数据(数组指针，2维方式)
int GetSaddlePoint1D(int *, int, int, int *, int *); // 求一个二维数组中的鞍点
int GetSaddlePoint2D(int m, int n, int (*a)[n], int *, int *); // 求一个二维数组中的鞍点(数组指针，2维方式)

void test1D(void); // 测试用1维方式操作2维数组查找鞍点
void test2D(void); // 测试采用变长数组，用数组指针操作2维数组查找鞍点

int main(void)
{
    test1D();
    test2D();

    return 0;
}

// 测试函数
void test1D(void)
{
    /*
        矩阵1：1   2   3   4   5
                 2   4   6   8   10
                 3   6   9   12  15
                 4   8   12   16  20
        矩阵2：1   12    3    4    5
               2    4    16   8    10
               3    6    9    12    15
               4    8    12    16    20
         */
//
    // 声明数组
    int a[][3] =
    {
        {1, 6, 8}, {2, 4, 7}, {3, 5, 9}
    };

    int i, m = 0, n = 0;
    int nCount = 0;

    // 计算数组的行列数
    m = sizeof(a) / sizeof(a[0]);
    n = sizeof(a[0]) / sizeof(a[0][0]);

    // 定义用于存储鞍行、列位置的动态数组指针
    int *pRow = NULL, *pCol = NULL;

    // 动态数组的大小(假定有m * n个鞍点)
    int nSize = m * n * sizeof(int);

    if ((pRow = (int *)malloc(nSize)) == NULL)
    {
        exit(1); // 内存分配失败
    }

    memset(pRow, 0, nSize); // 清0

    if ((pCol = (int *)malloc(nSize)) == NULL)
    {
        free(pRow); // 释放内存
        exit(1); // 内存分配失败
    }

    memset(pCol, 0, nSize); // 清0

    printf("the 2D array is: \n");
    Output1D((int *)a, m, n); // 输出原始数组

    nCount = GetSaddlePoint1D((int*)a, m, n, pRow, pCol);

    if(nCount != 0)
    {
        printf("\nThe total saddle is: %d, they are: \n", nCount);

        for(i = 0; i < nCount; i++)
        {
            printf("a[%d][%d] = %d\n", pRow[i], pCol[i], a[pRow[i]][pCol[i]]);
        }
    }
    else
    {
        printf("There is no saddle(s)!\n");
    }

    free(pRow);
    free(pCol);
}

void test2D(void)
{
    /*
        矩阵1：1   2   3   4   5
                 2   4   6   8   10
                 3   6   9   12  15
                 4   8   12   16  20
        矩阵2：1   12    3    4    5
               2    4    16   8    10
               3    6    9    12    15
               4    8    12    16    20
         */
//
    // 声明数组
    int a[][5] =
    {
        {1, 2, 3, 4, 5},
        {2, 4, 6, 8, 10},
        {3, 6, 9, 12, 15},
        {4, 8, 12, 16, 20}
    };

    int i, m = 0, n = 0;
    int nCount = 0;

    // 计算数组的行列数
    m = sizeof(a) / sizeof(a[0]);
    n = sizeof(a[0]) / sizeof(a[0][0]);

    // 定义用于存储鞍行、列位置的动态数组指针
    int *pRow = NULL, *pCol = NULL;

    // 动态数组的大小(假定有m * n个鞍点)
    int nSize = m * n * sizeof(int);

    if ((pRow = (int *)malloc(nSize)) == NULL)
    {
        exit(1); // 内存分配失败
    }

    memset(pRow, 0, nSize); // 清0

    if ((pCol = (int *)malloc(nSize)) == NULL)
    {
        free(pRow); // 释放内存
        exit(1); // 内存分配失败
    }

    memset(pCol, 0, nSize); // 清0

    printf("the 2D array is: \n");
    Output2D(m, n, a); // 输出原始数组

    nCount = GetSaddlePoint2D(m, n, a, pRow, pCol);

    if(nCount != 0)
    {
        printf("\nThe total saddle is: %d, they are: \n", nCount);

        for(i = 0; i < nCount; i++)
        {
            printf("a[%d][%d] = %d\n", pRow[i], pCol[i], a[pRow[i]][pCol[i]]);
        }
    }
    else
    {
        printf("There is no saddle(s)!\n");
    }

    free(pRow);
    free(pCol);
}

//------------------------------------------------
// 名称：void Input1D(int *a, int m, int n)
// 功能：录入数组各元素的值
// 参数：
//           [int *a] --- 整型指针，指向二维数组起始地址(&a[0][0])
//           [int m] --- 数组行数
//           [int n] --- 数组列数
// 返回：无
// 作者：耿楠
// 日期：2010年12月16日
//------------------------------------------------
void Input1D(int *a, int m, int n)
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            // 等价于&a[i][j]
            // a + i * n，找到第i行，
            // (a + i * n) + j，找到第j列
            scanf("%d", a + i * n + j);
        }
    }
}

//------------------------------------------------
// 名称：void Output1D(int *a, int m, int n)
// 功能：显示数组各元素的值
// 参数：
//           [int *a] --- 整型指针，指向二维数组起始地址(&a[0][0])
//           [int m] --- 数组行数
//           [int n] --- 数组列数
// 返回：无
// 作者：耿楠
// 日期：2010年12月16日
//------------------------------------------------
void Output1D(int *a, int m, int n)
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            //<==>a[i][j]
            //a + i * n，找到第i行，
            //(a + i * n) + j，找到第j列
            printf("%8d", *(a + i * n + j));
        }

        printf("\n");
    }
}

//------------------------------------------------
// 名称：void Input2D(int m, int n, int (*p)[n])
// 功能：录入数组各元素的值，通过变长数组，数组指针的形式实现
// 参数：
//           [int m] --- 数组行数
//           [int n] --- 数组列数，必须在数组指针形参之前，
//                           因为数组指针指向的数组是变长数组
//           [int (*p)[n]] --- 数组指针，指向二维数组(变长数组，需要C99)
// 返回：无
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
void Input2D(int m, int n, int (*p)[n])
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }
}

//------------------------------------------------
// 名称：void Output2D(int m, int n, int (*p)[n])
// 功能：显示数组各元素的值，通过变长数组，数组指针的形式实现
// 参数：
//           [int m] --- 数组行数
//           [int n] --- 数组列数，必须在数组指针形参之前，
//                           因为数组指针指向的数组是变长数组
//           [int (*p)[n]] --- 数组指针，指向二维数组(变长数组，需要C99)
// 返回：无
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
void Output2D(int m, int n, int (*p)[n])
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%8d", p[i][j]);
        }

        printf("\n");
    }
}

//------------------------------------------------
// 名称：int GetMaxPos(int *a, int n)
// 功能：查找一个数组中的最大值的位置
// 参数：
//           [int *a] --- 整型指针，指向一维数组起始地址
//           [int n] --- 数组长度
// 返回：int --- 最大值的位置
// 作者：耿楠
// 日期：2010年12月16日
//------------------------------------------------
int GetMaxPos(int *a, int n)
{
    int max, Pos = 0;
    int i;

    max = a[0]; // 最大值初始值，常用a[0]

    for(i = 0; i < n; i++)
    {
        if(a[i] > max)
        {
            max = a[i];
            Pos = i; // 更新
        }
    }

    return Pos;
}

//------------------------------------------------
// 名称：int GetMinPos(int *a, int n)
// 功能：查找一个数组中的最小值的位置
// 参数：
//           [int *a] --- 整型指针，指向一维数组起始地址
//           [int n] --- 数组长度
// 返回：int --- 最小值的位置
// 作者：耿楠
// 日期：2010年12月16日
//------------------------------------------------
int GetMinPos(int *a, int n)
{
    int min, Pos = 0;
    int i;

    min = a[0]; // 最小值初始值，常用a[0]

    for(i = 0; i < n; i++)
    {
        if(a[i] < min)
        {
            min = a[i];
            Pos = i; // 更新
        }
    }

    return Pos;
}

//------------------------------------------------
// 名称：void GetOneRow1D(int *a, int *p, int n, int i)
// 功能：提取二维数组中指定行(按一维方式访问)
// 参数：
//           [int *a] --- 整型指针，指向二维数组起始地址(&a[0][0])
//           [int *p] --- 整型指针，指向结果一维数组
//           [int n] --- 二维数组列数
//           [int i] --- 需要提取的行
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
void GetOneRow1D(int *a, int *p, int n, int i)
{

    int nRow = n * sizeof(int); // 一行占有的字节数
    int *pt = a + i * n; // 计算第i行的起始地址

    memcpy(p, pt, nRow); // 数据拷贝
}

//------------------------------------------------
// 名称：void GetOneRow2D(int n, int (*a)[n], int *p, int i)
// 功能：提取二维数组中指定行(采用变长数组形参实现)
// 参数：
//           [int n] --- 二维数组列数，必须在数组指针形参之前，
//                           因为数组指针指向的数组是变长数组
//           [int (*a)[n]] --- 数组指针，指向二维数组(变长数组，需要C99)
//           [int *p] --- 整型指针，指向结果一维数组

//           [int i] --- 需要提取的行
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
void GetOneRow2D(int n, int (*a)[n], int *p, int i)
{

    int nRow = n * sizeof(int); // 一行占有的字节数

    memcpy(p, a[i], nRow); // 数据拷贝
}

//------------------------------------------------
// 名称：void GetOneCol1D(int *a, int *p, int m, int n, int j)
// 功能：提取二维数组中指定列(按一维方式访问)
// 参数：
//           [int *a] --- 整型指针，指向二维数组起始地址(&a[0][0])
//           [int *p] --- 整型指针，指向结果一维数组
//           [int m] --- 数组行数
//           [int n] --- 二维数组列数
//           [int j] --- 需要提取的列
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
void GetOneCol1D(int *a, int *p, int m, int n, int j)
{
    //取出第是j列每行的元素
    for(int i = 0; i < m; i++)
    {
        p[i] = *(a + i * n + j);
    }
}

//------------------------------------------------
// 名称：void GetOneCol2D(int m, int n, int (*a)[n], int *p, int j)
// 功能：提取二维数组中指定列(采用数组指针形参实现)
// 参数：
//           [int m] --- 数组行数
//           [int n] --- 二维数组列数，必须在数组指针形参之前，
//                           因为数组指针指向的数组是变长数组
//           [int (*a)[n]] --- 数组指针，指向二维数组(变长数组，需要C99)
//           [int *p] --- 整型指针，指向结果一维数组
//           [int j] --- 需要提取的列
// 返回：[void] --- 无
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
void GetOneCol2D(int m, int n, int (*a)[n], int *p, int j)
{
    //取出第是j列每行的元素
    for(int i = 0; i < m; i++)
    {
        p[i] = a[i][j];
    }
}

//------------------------------------------------
// 名称：int GetSaddlePoint1D(int *a, int m, int n, int *pRow, int *pCol)
// 功能：求二维数组中的鞍点位置及其个数
// 参数：
//           [int *a] --- 整型指针，指向数组起始地址
//           [int m] --- 数组行数
//           [int n] --- 数组列数
//           [int *pRow] --- 鞍点的行位置数组指针
//           [int *pCol] --- 鞍点的列位置数组指针
// 返回：int --- 鞍点位置及其个数
// 作者：耿楠
// 日期：2010年12月16日
//------------------------------------------------
int GetSaddlePoint1D(int *a, int m, int n, int *pSaddleRow, int *pSaddleCol)
{
    int i, nSizeRow = 0, nSizeCol = 0;
    int *pRow = NULL, *pCol = NULL;
    int nMinRowPos, nMaxColPos;
    int nCount = 0;

    nSizeRow = n * sizeof(int); // 每行的长度
    nSizeCol = m * sizeof(int); // 每列的长度

    if ((pRow = (int *)malloc(nSizeRow)) == NULL)
    {
        exit(1); // 内存分配失败
    }

    memset(pRow, 0, nSizeRow); // 清0

    if ((pCol = (int *)malloc(nSizeCol)) == NULL)
    {
        free(pRow); // 释放内存
        exit(1); // 内存分配失败
    }

    memset(pCol, 0, nSizeCol); // 清0

    for(i = 0; i < m; i++)
    {
        // 提取第i行的数据
        GetOneRow1D(a, pRow, n, i);
        // 找到第i行的最大值的位置
        nMaxColPos = GetMaxPos(pRow, n);

        // 提取第nMaxColPos列的数据
        GetOneCol1D(a, pCol, m, n, nMaxColPos);

        // 找到该列最小值位置
        nMinRowPos = GetMinPos(pCol, m);

        //列上最小值位于该行，则找到鞍点
        if(nMinRowPos == i)
        {
            pSaddleRow[nCount] = nMinRowPos;
            pSaddleCol[nCount] = nMaxColPos;
            nCount++;
        }
    }

    //释放空间
    free(pRow);
    free(pCol);

    //返回鞍点个数
    return nCount;
}

//------------------------------------------------
// 名称：int GetSaddlePoint2D(int m, int n, int (*a)[n], int *pRow, int *pCol)
// 功能：求二维数组中的鞍点位置及其个数(采用数组指针形参实现)
// 参数：
//           [int m] --- 数组行数
//           [int n] --- 二维数组列数，必须在数组指针形参之前，
//                           因为数组指针指向的数组是变长数组
//           [int (*a)[n]] --- 数组指针，指向二维数组(变长数组，需要C99)
//           [int *pRow] --- 鞍点的行位置数组指针
//           [int *pCol] --- 鞍点的列位置数组指针
// 返回：int --- 鞍点位置及其个数
// 作者：耿楠
// 日期：2017年11月22日
//------------------------------------------------
int GetSaddlePoint2D(int m, int n, int (*a)[n], int *pSaddleRow, int *pSaddleCol)
{
    int i, nSizeRow = 0, nSizeCol = 0;
    int *pRow = NULL, *pCol = NULL;
    int nMinRowPos, nMaxColPos;
    int nCount = 0;

    nSizeRow = n * sizeof(int); // 每行的长度
    nSizeCol = m * sizeof(int); // 每列的长度

    if ((pRow = (int *)malloc(nSizeRow)) == NULL)
    {
        exit(1); // 分配内存失败
    }

    memset(pRow, 0, nSizeRow); // 清0

    if ((pCol = (int *)malloc(nSizeCol)) == NULL)
    {
        free(pRow); // 释放内存
        exit(1); // 分配内存失败
    }

    memset(pCol, 0, nSizeCol); // 清0

    for(i = 0; i < m; i++)
    {
        // 提取第i行的数据
        GetOneRow2D(n, a, pRow, i);
        // 找到第i行的最大值的位置
        nMaxColPos = GetMaxPos(pRow, n);

        // 提取第nMaxColPos列的数据
        GetOneCol2D(m, n, a, pCol, nMaxColPos);

        // 找到该列最小值位置
        nMinRowPos = GetMinPos(pCol, m);

        //列上最小值位于该行，则找到鞍点
        if(nMinRowPos == i)
        {
            pSaddleRow[nCount] = nMinRowPos;
            pSaddleCol[nCount] = nMaxColPos;
            nCount++;
        }
    }

    //释放空间
    free(pRow);
    free(pCol);

    //返回鞍点个数
    return nCount;
}



