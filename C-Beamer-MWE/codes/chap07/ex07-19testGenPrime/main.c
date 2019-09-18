/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：产生指定范围内质数的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年11月07日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> // 需要C99/C11支持

#define N 1000

// 函数原型

// 迭代法
unsigned int GenPrimeItr(unsigned int); // 简单迭代法

// 筛选法
unsigned int GenPrimeSieve(unsigned int); // 简单筛选法
unsigned int GenPrimeChkSieve(unsigned int); // 另一筛选法

// IsPrime函数类型重定义
typedef unsigned int (*GenPrimeFooType)(unsigned int);

// 测试函数(用typedef重定义类型声明)
void TestTimeConsuming(unsigned int, GenPrimeFooType, char *); // 测试时间效率

int main()
{
    // 函数指针数组(用typedef重定义类型声明)
    GenPrimeFooType pGenPrimeFoo[] =
    {
        GenPrimeItr,                   // 简单迭代法
        GenPrimeSieve,                   // 简单筛选法
        GenPrimeChkSieve, // 另一筛选法
        NULL
    };

    // 函数名称数组
    char *pGenPrimeName[] =
    {
        "01. GenPrimeItr: ",                   // 简单迭代法
        "02. GenPrimeSieve: ",                   // 简单筛选法
        "03. GenPrimeChkSieve: ", // 快速筛选法
        NULL
    };

    int m;
    int i = 0;

    //m = 50000; // 50000以内共5133个质数
    m = 1000000; // 1,000,000 以内共78498个质数

    // 测试时间效率(以函数指针是否为NULL做为循环结束条件)
    while(pGenPrimeFoo[i] != NULL)
    {
        TestTimeConsuming(m, pGenPrimeFoo[i], pGenPrimeName[i]);
        i++;
    }

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void TestTimeConsuming(unsigned int m, GenPrimeFooType pf, char *pfn)
// 功能: 测试时间效率
// 参数:
//       [int m] --- 需要判断的整数
//       [GenPrimeFooType pf] --- 质数判断函数函数指针
//       [char *pfn] --- 算法名称字符串指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
void TestTimeConsuming(unsigned int m, GenPrimeFooType pf, char *pfn)
{
    unsigned int cnts = 0;
    clock_t start;  // 开始时间
    clock_t end; // 结束时间
    double duration = 0.0; // 程序执行时间，单位秒

    // 测试时间效率
    start = clock();

    cnts = pf(m); // 生成质数表

    end = clock();

    //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%stotal = %d , time = %lf s.\n", pfn, cnts,  duration);
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrime(unsigned int n)
// 功能: 判断一个整数是否为质数
// 算法: 先尝试除2和3，然后穷举[5, √n ]中步长为6的i和i+2中所有数，看n是不是能被这些数整除。
//          任意一个除2和3以外的整数都可以表示为6k+i，其中i = -1, 0, 1, 2, 3, 4;
//          而 (6k + 0), (6k + 2), (6k + 4)能够被2整除，(6k + 3)能够被3整除;
//          因此，只需要判断6k ± 1 ≤ √n，也就是[5, √n ]中步长为6的i和i+2中所有数。
//          如：
//          5 6 7 8 9 10 11 12 13 14 15 16 17
//          ^   ^            ^
//           i   i+2         i+6
//          算法详解：https://en.wikipedia.org/wiki/Primality_test。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月07日
// 备注: 只是迭代法中判断一个数是不是质数的辅助函数，不需要进行原型声明。
//-----------------------------------------------------------------------------------------------
bool IsPrime(unsigned int n)
{
    int div = 2;
    int top = n;

    // 2和3都质数
    if(n <= 3)
    {
        return n > 1;
    }

    // 2和3的倍数不是质数
    if((n % 2 == 0) || (n % 3 == 0))
    {
        return false;
    }

    // 如果能被[5, √n]中任意一个div或div + 2整除，则不是质数
    for(div = 5; div * div <= top; div += 6)
    {
        if((n % div == 0) || (n % (div + 2) == 0))
        {
            return false;
        }
    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: unsigned int GenPrimeItr(unsigned int n)
// 功能: 迭代法产生指定范围的质数表
// 算法: 循环并判断每一个数是不是质数来生成质数表
// 参数:
//       [int n] --- 质数范围
// 返回: [unsigned int]  --- 返回质数总数
// 作者: 耿楠
// 日期: 2018年11月07日
//-----------------------------------------------------------------------------------------------
unsigned int GenPrimeItr(unsigned int n)
{
    int i;
    unsigned int cnts = 0;

    for(i = 2; i <= n; i++)
    {
        if(IsPrime(i))
        {
            cnts++;
        }
    }

    return cnts;
}

//-----------------------------------------------------------------------------------------------
// 名称: unsigned int GenPrimeSieve(unsigned int n)
// 功能: 筛选法产生指定范围的质数表
// 算法: 采用筛选法生成，算法参考：
//          https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes。
// 参数:
//       [int n] --- 质数范围
// 返回: [unsigned int]  --- 返回质数总数
// 作者: 耿楠
// 日期: 2018年11月07日
//-----------------------------------------------------------------------------------------------
unsigned int GenPrimeSieve(unsigned int n)
{
    int i, j;
    unsigned int cnts = 0;

    // 声明bool数组并赋值为true(筛子).
    bool sieve[n + 1]; // 变长数组，需要C99及以后标准支持
    //bool *sieve = (bool *)malloc((n + 1) * sizeof(bool)); // 动态内存分配

    // 0和1不是质数
    sieve[0] = false;
    sieve[1] = false;

    for(i = 2; i <= n; i++)
    {
        sieve[i] = true;
    }

    // 从2 到sqrt(n).
    for (i = 2; i * i <= n; i++)
    {
        if (sieve[i])
        {
            // 删除i后的每一个i的倍数的数.
            for (j = (i * i); j <= n; j += i)
            {
                sieve[j] = false;
            }
        }
    }

    for(i = 2; i <= n; i++)
    {
        if(sieve[i])
        {
            cnts++;
        }
    }

    return cnts;
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetNextDiv(bool *sieve, int top, int p)
// 功能: 找出比p大而没有被删除的数q
// 参数:
//       [bool *sieve] --- 筛子数组指针
//       [int top] --- 数组上限
//       [int p] --- 当前整数
// 返回: [int]  --- 比p大而没有被删除的数
// 作者: 耿楠
// 日期: 2018年11月07日
// 备注: 这是一个仅由GenPrimeChkSieve调用的辅助函数，不需要进行原型声明。
//-----------------------------------------------------------------------------------------------
int GetNextDiv(bool *sieve, int top, int p)
{
    int q = p + 1;

    while (q < top && sieve[q] == false) 	/*  查找未被筛去的q */
    {
        q++;
    }
    return q;
}

//-----------------------------------------------------------------------------------------------
// 名称: unsigned int GenPrimeChkSieve(unsigned int n)
// 功能: 筛选法产生指定范围的质数表
// 算法: 采用改进筛选法生成，算法参考：
//          https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes。
// 参数:
//       [int n] --- 质数范围
// 返回: [unsigned int]  --- 返回质数总数
// 作者: 耿楠
// 日期: 2018年11月07日
//-----------------------------------------------------------------------------------------------
unsigned int GenPrimeChkSieve(unsigned int n)
{
    int p, q, i;
    unsigned int top = n + 1;
    unsigned int cnts = 0;


    // 声明bool数组并赋值为true(筛子).
    bool sieve[top]; // 变长数组，需要C99及以后标准支持
    //bool *sieve = (bool *)malloc(top * sizeof(bool)); // 动态内存分配

    // 0和1不是质数
    sieve[0] = false;
    sieve[1] = false;

    for(i = 2; i <= n; i++)
    {
        sieve[i] = true;
    }

    for (p = 2; p * p < top; p = GetNextDiv(sieve, top, p))
    {
        for (q = p; p * q < top; q = GetNextDiv(sieve, top, q))
        {
            for (i = p * q; i < top; i *= p) 		/* 删除i */
            {
                sieve[i] = false;
            }
        }
    }

    for(i = 0; i <= n; i++)
    {
        if(sieve[i])
        {
            cnts++;
        }
    }

    return cnts;
}
