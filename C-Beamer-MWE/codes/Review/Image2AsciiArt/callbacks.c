#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "callbacks.h"

//--------------------------------------------------------------------------
// 名称：double GetAverage(unsigned char *pdata, int pixW, int pixH)
// 功能：获取区块数据的平均值
// 参数：
//           [unsigned char *pdata] --- 区块数据指针
//           [int pixW] --- 需要处理成单个字符的区块宽度
//           [int pixH] --- 需要处理成单个字符的区块高度
// 返回：无
// 作者：耿楠
// 日期：2019年1月16日
//--------------------------------------------------------------------------
double GetAverage(unsigned char *pdata, int pixW, int pixH)
{
    size_t size = pixW * pixH;
    double sum = 0.0;
    double pixlevel = 0.0;

    unsigned char *p = pdata;

    for(int i = 0; i < size; i++)
    {
        // 计算一个像素的归一化灰度值(0.0-1.0)，注意颜色排列为：B、G、R
        pixlevel = 0.11 * p[2] / 255 + 0.6 * p[1] / 255 + 0.29 * p[0] / 255;
        sum += pixlevel;
        p += 3;
    }

    return sum / size;
}

//-----------------------------------------------------------------------------------------------
// 名称：int cmp(const void *a, const void *b)
// 功能：用于浮点数的比较大于函数
// 参数：
//       [const void *a] --- 第一个元素的起始地址
//       [const void *b] --- 第二个元素的起始地址
// 返回：[int] --- *a > *b返回1，否则返回0
// 注意：需要在函数内部进行强制地址类型转换，以实现浮点数比较
// 作者：耿楠
// 日期：2019年1月16日
// 备注：这是一个辅助函数，是GetMedian函数中的qsort函数的比较函数。
//-----------------------------------------------------------------------------------------------
int cmp(const void *a, const void *b)
{
    //return (*(double*)a > * (double*)b) ? 1 : 0;
    return ((*(double*)a - * (double*)b > 0) ? 1 : -1);
}

//--------------------------------------------------------------------------
// 名称：double GetMedian(unsigned char *pdata, int pixW, int pixH)
// 功能：获取区块数据的中值
// 参数：
//           [unsigned char *pdata] --- 区块数据指针
//           [int pixW] --- 需要处理成单个字符的区块宽度
//           [int pixH] --- 需要处理成单个字符的区块高度
// 返回：无
// 作者：耿楠
// 日期：2019年1月16日
//--------------------------------------------------------------------------
double GetMedian(unsigned char *pdata, int pixW, int pixH)
{
    size_t size = pixW * pixH;
    double result = 0.0;

    double *plev = malloc(size * sizeof(double));
    if(plev == NULL)
    {
        printf("Not enough memory!\n");
        return 0.0;
    }
    memset(plev, 0, size * sizeof(double));

    double div = 255.0 * 3.0;

    unsigned char *p = pdata;
    for(int i = 0; i < size; i++)
    {
        // 计算一个像素的归一化灰度值(0.0-1.0)，注意颜色排列为：B、G、R
        plev[i] = (p[2]  + p[1] + p[0]) / div;
        p += 3;
    }

    qsort(plev, size, sizeof(double), cmp);
    result = plev[size / 2];

    // 释放内存
    free(plev);

    return result;
}

//--------------------------------------------------------------------------
// 名称：double * GetLoGKer(double d, int m, int n)
// 功能：生成LOG算子
// 参数：
//           [double d] --- 方差
//           [int m] --- LOG算子高度
//           [int n] --- LOG算子宽度
// 返回：[double * ] --- LOG算子首地址
// 作者：耿楠
// 日期：2019年1月16日
// 备注：该函数将动态生成数组，调用结束后需要释放内存空间，
//          另，该函数是一个辅助函数。
//--------------------------------------------------------------------------
double * GetLoGKer(double d, int m, int n)
{
    // 申请内存
    double *p = malloc(m * n * sizeof(double));
    if(p == NULL)
    {
        fprintf(stderr, "内存不足!\n");
        exit(EXIT_FAILURE);
    }
    // 初始化
    memset(p, 0, m * n * sizeof(double));

    int x = (n - 1) / 2;
    int y = (m - 1) / 2;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            p[i + j * n] = exp(-((x - i) * (x - i) + (y - j) * (y - j) / (2 * d * d))) *
                           ((x - i) * (x - i) + (y - j) * (y - j) - 2 * d * d) / (d * d * d * d);
        }
    }

    double min = p[0];
    for(int i = 0; i < m * n; i++)
    {
        if(p[i] < min)
        {
            min = p[i];
        }
    }

    for(int i = 0; i < m * n; i++)
    {
        p[i] += min;
    }

    double sum = 0.0;
    for(int i = 0; i < m * n; i++)
    {
        sum += p[i];
    }

    for(int i = 0; i < m * n; i++)
    {
        p[i] /= sum;
    }

    return p;
}

//--------------------------------------------------------------------------
// 名称：double GetLoG(unsigned char *pdata, int pixW, int pixH)
// 功能：获取区块数据的中值
// 参数：
//           [unsigned char *pdata] --- 区块数据指针
//           [int pixH] --- 需要处理成单个字符的区块高度
//           [int pixW] --- 需要处理成单个字符的区块宽度
// 返回：无
// 作者：耿楠
// 日期：2019年1月16日
//--------------------------------------------------------------------------
double GetLoG(unsigned char *pdata, int pixW, int pixH)
{
    size_t size = pixW * pixH;
    double result = 0.0;
    double pixlevel = 0.0;

    // 生成LoG算子
    double *pLoG = GetLoGKer(1, pixH, pixW);

    unsigned char *p = pdata;
    for(int i = 0; i < size; i++)
    {
        // 计算一个像素的归一化灰度值(0.0-1.0)，注意颜色排列为：B、G、R
        pixlevel = 0.11 * p[2] / 255 + 0.6 * p[1] / 255 + 0.29 * p[0] / 255;
        result += pixlevel * pLoG[i];
        p += 3;
    }

    // 释放内存
    free(pLoG);

    return result;
}

