/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：矩阵原地转置算法的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月1日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define M 4
#define N 2

void Swap(int *, int *);  // 交换两个数
void ReverseArr(int *, size_t); // 数组反向
void MoveData(int *, size_t); // 数组循环右移
void TransposeInPlace(); // 矩阵原地转置
void Output(int *, int, int); // 输出矩阵

// 主函数，进行测试
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
    int *pm = malloc(M * N * sizeof(int)); // 申请内存，用1维数组模拟二维数组
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
// 名称: void Swap(int *pa, int *pb)
// 功能: 交换两个数(异或操作实现)
// 参数:
//      [int *pa] --- 要交换的第1个数的指针
//      [int *pb] --- 要交换的第2个数的指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月1日
//-----------------------------------------------------------------------------------------------
void Swap(int *pa, int *pb)
{
    *pa = *pa^*pb;
    *pb = *pa^*pb;
    *pa = *pa^*pb;
}

//-----------------------------------------------------------------------------------------------
// 名称: void ReverseArr(int *pa, size_t size)
// 功能: 通过首尾交换，将数组反向
// 参数:
//      [int *pa] --- 数组的起始地址
//      [size_t size] --- 数组长度
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月1日
//-----------------------------------------------------------------------------------------------
void ReverseArr(int *pa, size_t size)
{
    int i = 0;
    int j = size - 1;
    while(i < j)
    {
        Swap(pa + i, pa + j);
        i++;
        j--;
    }

}

//-----------------------------------------------------------------------------------------------
// 名称: void MoveData(int *pa, size_t size)
// 功能: 通过两次数组反向，实现循环右移1个数组元素
// 参数:
//      [int *pa] --- 数组的起始地址
//      [size_t size] --- 数组长度
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月1日
//-----------------------------------------------------------------------------------------------
void MoveData(int *pa, size_t size)
{
    if(size == 1)
    {
        return ;
    }

    ReverseArr(pa, size - 1);  // 反向前size-1个元素
    ReverseArr(pa, size); // 反向size个元素，实现循环移位
}

//-----------------------------------------------------------------------------------------------
// 名称: void TransposeInPlace(int *pm, int m, int n)
// 功能: 矩阵原地转置(循环处理所有数据移动环)
// 参数:
//      [int *pmtx] --- 矩阵指针(一维模式)
//      [int m] --- 二维数组行数
//      [int n] --- 二维数组列数
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月1日
//-----------------------------------------------------------------------------------------------
void TransposeInPlace(int *pm, int m, int n)
{
    int from, to, offset, step;
    int i, j;
    step = n;
    to = offset = 0;
    for(i = 0; i < n; i++)
    {
        from = i + offset;
        for( j = 0; j < m; j++)
        {
            MoveData(pm + to, from - to + 1);
            from += step;
            to++;
        }
        step--;
        offset += m - 1;
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
// 日期: 2018年12月1日
//-----------------------------------------------------------------------------------------------
void Output(int *pm, int m, int n)
{
    for(int i = 0; i < m * n; ++i)
    {
        if((i + 1) % n == 0)
        {
            printf("%d\n", pm[i]); // 换行
        }
        else
        {
            printf("%d ", pm[i]);
        }
    }
}
