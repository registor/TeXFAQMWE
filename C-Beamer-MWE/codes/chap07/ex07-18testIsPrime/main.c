/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：判断一个数是不是质数的演示代码。
*           质数定义为在大于1的自然数中，除了1和它本身以外不再有其他因数，否则称为合数。
*           2是已知的最小质数。
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年11月06日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // 需要C99/C11支持

#define N 1000

// 函数原型

// 试除法
bool IsPrimeExhmustion(unsigned int); // 简单穷举
bool IsPrimeBiDiv(unsigned int); // 折半穷举
bool IsPrimeBiOddDiv(unsigned int); // 除2外的奇数穷举
bool IsPrimeSqrtDiv(unsigned int); // 开方穷举
bool IsPrimeSqrtOddDiv(unsigned int); // 除2外的奇数开方穷举
bool IsPrimeSqrtStepSixDiv(unsigned int); // 除2和3，从5开始以步长为6穷举
bool IsPrimeSqrtStepTwoFourDiv(unsigned int); // 除2和3，从5开始步长为2/4交替穷举

// 筛选法(适宜于筛选一组数中的质数，不适宜于判断一个数是不是素数)
bool IsPrimeSieve(unsigned int); // 简单筛选

// IsPrime函数类型重定义
typedef bool (*IsPrimeFooType)(unsigned int);

// 测试函数(用typedef重定义类型声明)
void TestTimeConsuming(unsigned int, IsPrimeFooType, char *); // 测试时间效率

int main()
{
    // 函数指针数组(用typedef重定义类型声明)
    IsPrimeFooType pIsPrimeFoo[] =
    {
        IsPrimeExhmustion,                   // 穷举法
        IsPrimeBiDiv,                   // 折半穷举法
        IsPrimeBiOddDiv, // 除2外的奇数穷举
        IsPrimeSqrtDiv, // 开方穷举
        IsPrimeSqrtOddDiv, // 除2外的奇数开方穷举
        IsPrimeSqrtStepSixDiv, // 除2和3，从5开始步长为6的穷举
        IsPrimeSqrtStepTwoFourDiv, // 除2和3，从5开始步长为2/4交替穷举
        IsPrimeSieve, // 筛选法
        NULL
    };

    // 函数名称数组
    char *pIsPrimeName[] =
    {
        "01. Exhmustion: ",                   // 穷举法
        "02. BiDiv: ",                   // 折半穷举法
        "03. BiOddDiv: ", // 除2外的奇数穷举
        "04. SqrtDiv: ", // 开方穷举
        "05. SqrtOddDiv: ",  // 除2外的奇数开方穷举
        "06. SqrtStepSixDiv: ", // 除2和3，从5开始步长为6的穷举
        "07. SqrtStepTwoFourDiv: ", // 除2和3，从5开始步长为2/4交替穷举
        "08. Sieve: ", // 筛选法
        NULL
    };

    int m;
    int i = 0;

    m = 997;
    //m = 1000000000;

    // 测试时间效率(以函数指针是否为NULL做为循环结束条件)
    while(pIsPrimeFoo[i] != NULL)
    {
        TestTimeConsuming(m, pIsPrimeFoo[i], pIsPrimeName[i]);
        i++;
    }

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void TestTimeConsuming(unsigned int m, IsPrimeFooType pf, char *pfn)
// 功能: 测试时间效率
// 参数:
//       [int m] --- 需要判断的整数
//       [IsPrimeFooType pf] --- 质数判断函数函数指针
//       [char *pfn] --- 算法名称字符串指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
void TestTimeConsuming(unsigned int m, IsPrimeFooType pf, char *pfn)
{
    int i;
    clock_t start;  // 开始时间
    clock_t end; // 结束时间
    double duration = 0.0; // 程序执行时间，单位秒

    // 执行N次测试，用累计时间进行判断
    start = clock();
    for(i = 0; i < N; i++)
    {
        pf(m);
    }
    end = clock();

    //CLOCKS_PER_SEC是一个常数，表示机器时钟每秒所使用的CPU时钟单元
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    if(pf(m))
    {
        printf("%s%d is a prime, consuming time = %lf s.\n", pfn, m,  duration);
    }
    else
    {
        printf("%s%d is not a prime, consuming time = %lf s.\n", pfn, m,  duration);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeExhmustion(unsigned int n)
// 功能: 试除法判断一个整数是否为质数
// 算法: 穷举[2, n -1]中所有的数，看n是不是能被这些数整除，
//          只要能被一个整除，则n是合数，否则，n是质数。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
bool IsPrimeExhmustion(unsigned int n)
{
    int div = 2;
    int top = n;

    // 2是已知最小的质数
    if(n <= 1)
    {
        return false;
    }

    // 如果能被[2, n -1]中任意一个数整除，则不是质数
    for(div = 2; div < top; div++)
    {
        if(n % div == 0)
        {
            return false;
        }
    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeBiDiv(unsigned int n)
// 功能: 试除法判断一个整数是否为质数
// 算法: 穷举[2, n / 2]中所有的数，看n是不是能被这些数整除，
//          只要能被一个整除，则n是合数，否则，n是质数。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
bool IsPrimeBiDiv(unsigned int n)
{
    int div = 2;
    int top = n / 2;

    // 2是已知最小的质数
    if(n <= 1)
    {
        return false;
    }

    // 如果能被[2, n /2]中任意一个数整除，则不是质数
    for(div = 2; div <= top; div++)
    {
        if(n % div == 0)
        {
            return false;
        }
    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeBiOddDiv(unsigned int n)
// 功能: 试除法判断一个整数是否为质数
// 算法: 先尝试除2，然后穷举[3, n / 2]中所有的奇数，看n是不是能被这些数整除，
//          只要能被一个整除，则n是合数，否则，n是质数。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
bool IsPrimeBiOddDiv(unsigned int n)
{
    int div = 2;
    int top = n / 2;

    // 2是已知最小的质数
    if(n <= 2)
    {
        return n > 1;
    }

    // 能被2整除，偶数不是质数
    if( n % 2 == 0)
    {
        return false;
    }

    // 如果能被[3, n / 2]中任意一个奇数整除，则不是质数
    for(div = 3; div <= top; div += 2)
    {
        if(n % div == 0)
        {
            return false;
        }
    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeSqrtDiv(unsigned int n)
// 功能: 试除法判断一个整数是否为质数
// 算法: 穷举[2, √n ]中所有的数，看n是不是能被这些数整除，
//          只要能被一个整除，则n是合数，否则，n是质数。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
bool IsPrimeSqrtDiv(unsigned int n)
{
    int div = 2;
    int top = n;

    // 2是已知最小的质数
    if(n <= 1)
    {
        return false;
    }

    // 如果能被[2, √n]中任意一个数整除，则不是质数
    for(div = 2; div * div <= top; div++)
    {
        if(n % div == 0)
        {
            return false;
        }
    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeSqrtOddDiv(unsigned int n)
// 功能: 试除法判断一个整数是否为质数
// 算法: 先尝试除2，然后穷举[3, √n ]中所有的奇数，看n是不是能被这些数整除，
//          只要能被一个整除，则n是合数，否则，n是质数。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月06日
//-----------------------------------------------------------------------------------------------
bool IsPrimeSqrtOddDiv(unsigned int n)
{
    int div = 2;
    int top = n;

    // 2是已知最小的质数
    if(n <= 2)
    {
        return n > 1;
    }

    // 判断是不是能被2整除
    if(n % 2 == 0)
    {
        return false;
    }

    // 如果能被[3, √n]中任意一个奇数整除，则不是质数
    for(div = 3; div * div <= top; div += 2)
    {
        if(n % div == 0)
        {
            return false;
        }
    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeSqrtStepSixDiv(unsigned int n)
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
//-----------------------------------------------------------------------------------------------
bool IsPrimeSqrtStepSixDiv(unsigned int n)
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
// 名称: bool IsPrimeSqrtStepTwoFourDiv(unsigned int n)
// 功能: 判断一个整数是否为质数
// 算法: 先尝试除2和3，然后穷举[5, √n ]中步长交替2和4中所有数，看n是不是能被这些数整除。
//          该算法是IsPrimeSqrtStepSixDiv算法的变形
//          任意一个除2和3以外的整数都可以表示为6k+i，其中i = -1, 0, 1, 2, 3, 4;
//          而 (6k + 0), (6k + 2), (6k + 4)能够被2整除，(6k + 3)能够被3整除;
//          因此，只需要判断6k ± 1 ≤ √n，也就是[5, √n ]中步长为6的i和i+2中所有数。
//          在一个步长6内需要的第1个除数的步长是2，第2个除数的步长是4，然后交替进行。
//          如：
//          5 6 7 8 9 10 11 12 13 14 15 16 17
//          ^   ^            ^       ^                 ^
//          算法详解：https://en.wikipedia.org/wiki/Primality_test。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月07日
//-----------------------------------------------------------------------------------------------
bool IsPrimeSqrtStepTwoFourDiv(unsigned int n)
{
    int div = 5; // 从5开始
    int top = n; // 判断上限
    int step = 2; // 交替因子初始值

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

    // 如果能被[5, √n]中步长交替2和4的数整除，则不是质数
    // 用for 实现
    for(div = 5; div * div <= top; div += step, step = 6 - step)
    {
        if(n % div == 0)
        {
            return false;
        }
    }

    // 用while实现
//    while(div * div <= top)
//    {
//        if(n % div == 0)
//        {
//            return false;
//        }
//        div += step;
//        step = 6 - step;
//    }

    // 否则是质数
    return true;
}

//-----------------------------------------------------------------------------------------------
// 名称: bool IsPrimeSieve(unsigned int n)
// 功能: 筛选法判断一个整数是否为质数
// 算法: 采用筛选法判断一个整数是否为质数，算法参考：
//          https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes。
// 参数:
//       [int n] --- 需要判断的整数
// 返回: [bool]  --- 是质数返回true(真)，否则返回false(假)
// 作者: 耿楠
// 日期: 2018年11月07日
// 备注: 该函数适宜于筛选指定范围内的质数，不适宜于判断一个数是不是质数。
//-----------------------------------------------------------------------------------------------
bool IsPrimeSieve(unsigned int n)
{
    int i, j;

    // 小于2，不是质数。
    if (n < 2)
    {
        return false;
    }

    // 声明bool数组并赋值为true(筛子).
    bool sieve[n]; // 变长数组，需要C99及以后标准支持
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

    return sieve[n];
}
