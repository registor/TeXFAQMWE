/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：矩阵原地转置算法的演示代码。
* 题目描述：(微软面试题)将一个MxN的矩阵存储在一个一维数组中，编程实现矩阵的转置。
* 要求：空间复杂度为O(1)---原地转置
*
* 思路：以一个4x2的矩阵A={1,2,3,4,5,6,7,8}进行分析，转置过程如下：
*          1[0] 2[1]
*          3[2] 4[3]  转置成2x4的矩阵：1[0] 3[1] 5[2] 7[3]
*          5[4] 6[5]                              2[4] 4[5] 6[6] 8[7]
*          7[6] 8[7]
*          其中方括号中的数字表示在一维数组中的下标。
*          矩阵的转置其实就是数组中元素的移动，具体的移动过程如下图(数字为下标值)：
*          0->0
*          1->4->2->1
*          2->1->4->2(重复)
*          3->5->6->3
*          4->2->1->4(重复)
*          5->6->3->5(重复)
*          6->3->5->6(重复)
*          7->7
*          显然，这些被移动的元素下标构成一个个的环：
*          下标1的元素移动到4，下标4的元素移动到2，下标2的元素移动到1。
*          在编写程序的时候，需要解决两个问题：
*          第一个是如何判定环是否重复（已处理过）；第二个是如何计算当前元素下标的前驱与后继。
*          第一个问题：如何判断环是重复已处理过的？
*          因为遍历整个数组时下标是从小到大的，所以如果是第一次遍历该环，
*          则第一个下标肯定是这个环中最小的。如果一个环被处理过，
*          那么总能找到一个它的后继是小于它的。从上图可以明显看出来。
*          第二个问题：如何计算当前元素下标的前驱与后继？
*          假设转置前某个元素的数组下标为i，则它所在行列为（i/N, i%N），
*          转置后所在行列则为（i%N, i/N），可计算转置后数组下标为(i%N)*M+i/N，此为i的后继。
*          假设转置后某个元素的数组下标为i，则它所在行列为（i/M, i%M），
*          则转置前所在行列为（i%M, i/M），可计算此时下标为(i%M)*N+i/M，此为i的前驱。
*
*          该算法参见：https://blog.csdn.net/lisonglisonglisong/article/details/28904665
*          该程序只是对文献中的代码进行了适当规范化。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年11月30日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define M 4
#define N 2

// 函数原型
int GetNext(int, int, int); /* 计算后继下标值 */
int GetPre(int, int, int); /* 计算前驱下标值 */
void MoveData(int *, int, int, int); /* 处理以下标i为起点的环 */
void TransposeInPlace(int *, int, int); /* 转置，即循环处理所有环 */
void Output(int *, int, int); /* 输出矩阵 */

/* 测试 */
int main()
{
    // 静态数组测试
    int matrix[M][N] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    printf("Before matrix transposition:\n");
    Output((int *)matrix, M, N); // 注意指针的类型转换(下同)
    TransposeInPlace((int *)matrix, M, N);
    printf("After matrix transposition:\n");
    Output((int *)matrix, N, M);

    // 动态数组测试
    int *pm= malloc(M* N * sizeof(int)); // 申请内存，用1维数组模拟二维数组
    int data = 1;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            *(pm + i * N + j) = data;
            data++;
        }
    }
    printf("Before dymatrix transposition:\n");
    Output(pm, M, N);
    TransposeInPlace(pm, M, N);
    printf("After dymatrix transposition:\n");
    Output(pm, N, M);

    // 释放空间
    free(pm);
    pm = NULL;

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: int GetNext(int i, int m, int n)
// 功能: 计算转置后的下标(后继)
// 算法: 对于一个MxN的二维数组，假设转置前某个元素的数组一维下标为i，
//          则它所在行列为（i/N, i%N），
//          转置后所在行列则为（i%N, i/N），
//          可计算转置后数组的一维下标为(i%N)*M+i/N，
//          此为i的后继。
// 参数:
//      [int i] --- 转置前某个元素在数组中的一维下标
//      [int m] --- 二维数组行数
//      [int n] --- 二维数组列数
// 返回: [int]  --- 转置后在数组中的一维下标
// 作者: 耿楠
// 日期: 2018年11月30日
//-----------------------------------------------------------------------------------------------
int GetNext(int i, int m, int n)
{
    return (i % n) * m + i / n;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetPre(int i, int m, int n)
// 功能: 计算转置后的下标(前驱)
// 算法: 对于一个MxN的二维数组，假设转置后某个元素的数组一维下标为i，
//          则它所在行列为（i/M, i%M），
//          则转置前所在行列为（i%M, i/M），
//          可计算此时一维下标为(i%M)*N+i/M，
//          此为i的前驱。
// 参数:
//      [int i] --- 转置后某个元素在数组中的一维下标
//      [int m] --- 二维数组行数
//      [int n] --- 二维数组列数
// 返回: [int]  --- 转置前在数组中的一维下标
// 作者: 耿楠
// 日期: 2018年11月30日
//-----------------------------------------------------------------------------------------------
int GetPre(int i, int m, int n)
{
    return (i % m) * n + i / m;
}

//-----------------------------------------------------------------------------------------------
// 名称: void MoveData(int *pmtx, int i, int m, int n)
// 功能: 处理以下标i为起点的数据移动环
// 参数:
//      [int *pmtx] --- 矩阵指针(一维模式)
//      [int i] --- 数组一维下标
//      [int m] --- 二维数组行数
//      [int n] --- 二维数组列数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月30日
//-----------------------------------------------------------------------------------------------
void MoveData(int *pmtx, int i, int m, int n)
{
    int temp = pmtx[i]; // 暂存
    int cur = i;    // 当前下标
    int pre = GetPre(cur, m, n); // 获得前驱
    while(pre != i)
    {
        pmtx[cur] = pmtx[pre];
        cur = pre;
        pre = GetPre(cur, m, n);
    }
    pmtx[cur] = temp;
}

//-----------------------------------------------------------------------------------------------
// 名称: void TransposeInPlace(int *pmtx, int m, int n)
// 功能: 矩阵原地转置(循环处理所有数据移动环)
// 参数:
//      [int *pmtx] --- 矩阵指针(一维模式)
//      [int m] --- 二维数组行数
//      [int n] --- 二维数组列数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月30日
//-----------------------------------------------------------------------------------------------
void TransposeInPlace(int *pmtx, int m, int n)
{
    for(int i = 0; i < m * n; ++i)
    {
        int next = GetNext(i, m, n);
        while(next > i) // 若存在后继小于i说明重复(跳过这一个数据移动移动环)
        {
            next = GetNext(next, m, n);
        }

        if(next == i)  // 处理当前环(需要处理)
        {
            MoveData(pmtx, i, m, n);
        }
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: void Output(int *pmtx, int m, int n)
// 功能: 输出矩阵
// 参数:
//      [int *pmtx] --- 矩阵指针(一维模式)
//      [int m] --- 二维数组行数
//      [int n] --- 二维数组列数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月30日
//-----------------------------------------------------------------------------------------------
void Output(int *pmtx, int m, int n)
{
    for(int i = 0; i < m * n; ++i)
    {
        if((i + 1) % n == 0)
        {
            printf("%d\n", pmtx[i]); // 换行
        }
        else
        {
            printf("%d ", pmtx[i]);
        }
    }
}