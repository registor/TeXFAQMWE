/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：求两个多项式和的演示代码。
* 题目描述：一个多项式可以表达为x的各次幂与系数乘积的和，比如：
*         2x6+3x5+12x3+6x+20
*         要求读入两个多项式，然后输出这两个多项式的和，
*         也就是把对应的幂上的系数相加然后输出。
*         程序要处理的幂最大为100。
* 输入格式:总共要输入两个多项式，每个多项式的输入格式如下：
*         每行输入两个数字，第一个表示幂次，第二个表示该幂次的系数，
*         所有的系数都是整数。第一行必须是最高幂，最后一行必须是0次幂。
*         注意第一行和最后一行之间不一定按照幂次降低顺序排列；
*         如果某个幂次的系数为0，则不出现在输入数据中；
*         0次幂的系数为0时还是会出现在输入数据中。
* 输出格式：从最高幂开始依次降到0幂，如：
*         2x6+3x5+12x3-6x+20
*         注意其中的x是小写字母x，而且所有的符号之间都没有空格，
*         如果某个幂的系数为0则不需要有那项。
* 输入样例：  6 2
*           5 3
*           3 12
*           1 6
*           0 20
*           6 2
*           5 3
*           2 12
*           1 6
*           0 20
* 输出样例：4x6+6x5+12x3+12x2+12x+40
*
* 解决思路：用数组的下标索引表示幂次，对应的元素值则为该幂次的系数。
*         用两个数组分别存储两个多项式，然后下标相同的元素相加。
*         该问题的最大难度在于如何处理输出结果，以满足要求。
*         算法详见代码注释。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年12月11日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

// 宏定义
#define MAXDEG 101
#define NUM 101

// 函数原型
void InitPolynomial(int *, int); // 初始化多项式
int InputPolynomial(int *, int); // 输入多项式
int OutputPolynomial(int *, int); // 输出多项式
void AddPolynomial(int *, int *, int); // 两个多项式相加

// 测试
int main()
{
    int Poly1[MAXDEG], Poly2[MAXDEG];

    // 输入并输出多项式1
    InputPolynomial(Poly1, MAXDEG);
    // OutputPolynomial(Poly1, MAXDEG); // 输出第1个多项式

    // 输入并输出多项式2
    InputPolynomial(Poly2, MAXDEG);
    // OutputPolynomial(Poly2, MAXDEG); // 输出第2个多项式

    // 求和，并将结果存储在多项式1后输出结果
    AddPolynomial(Poly1, Poly2, MAXDEG);
    OutputPolynomial(Poly1, MAXDEG); // 输出结果多项式
    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void InitPolynomial(int *pPoly, int n)
// 功能: 初始化多项式，将各幂次系数初始化为0
// 算法: 用数组下标表示幂次，将对应的元素置0
// 参数:
//      [int *pPoly] --- 表达多项式的数组指针
//      [int n] --- 数组长度
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void InitPolynomial(int *pPoly, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        pPoly[i] = 0; // 数组下标表示幂次
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int InputPolynomial(int *pPoly, int n)
// 功能: 输入多项式，将各幂次系数初始化为0
// 算法: 用输入的幂次作为下标，将系数赋值到对应的元素
// 参数:
//      [int *pPoly] --- 表达多项式的数组指针
//      [int n] --- 数组长度
// 返回: [int]  --- 最高幂次
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
int InputPolynomial(int *pPoly, int n)
{
    int power = 0, coeff = 0;

    int highpower = 0; // 记录最高幂次

    InitPolynomial(pPoly, n); // 初始化

    // 至少要输入1次，用do...while循环实现
    do
    {
        scanf("%d %d", &power, &coeff);
        pPoly[power] = coeff;
        if (highpower < power) // 最高幂次
        {
            highpower = power;
        }
    }while (power != 0);

    return highpower; // 返回最高幂次
}

//-----------------------------------------------------------------------------------------------
// 名称: int OutputPolynomial(int *pPoly, int n)
// 功能: 输出多项式
// 算法: 遍历数组，将不为0的值按要求的规则输出
// 参数:
//      [int *pPoly] --- 表达多项式的数组指针
//      [int n] --- 数组长度
// 返回: [int]  --- 输出的项数计数值
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
int OutputPolynomial(int *pPoly, int n)
{
    int i;

    int cnt = 0;

    // 输出2次幂及其以前的项(1次幂和0次幂需要特殊处理)
    for (i = n - 1; i > 1; i--)
    {
        if (pPoly[i] != 0)        // 只输出系数不为0的项
        {
            if (pPoly[i] == 1)  // 如果系数==1，比如40 1
            {
                if (cnt > 0)        // 如果不是第一次输出，则前面加正号+
                {
                    printf("+");
                }
                printf("x%d", i);        // 例如输出x40
            }
            else if (pPoly[i] == -1)        // 如果系数==-1，比如40 -1
            {
                printf("-x%d", i);        // 前面加负号-，系数-1省略，输出-x40
            }
            else        // 其他情况，系数不等于1，也不等于-1
            {
                if (pPoly[i] < 0)
                {
                    printf("%dx%d", pPoly[i], i);        // 系数小于0，直接输出
                }
                else
                {
                    if (cnt > 0)
                    {
                        printf("+");        // 如果系数大于0，且不是第一次输出，需要前面加正号+
                    }
                    printf("%dx%d", pPoly[i], i);
                }
            }
            cnt++;
        }
    }

    // 单独输出1次幂
    if (pPoly[1] != 0)        // pPoly[1]的系数不等于0
    {
        {
            if (pPoly[1] == 1)        // 如果系数==1
            {
                if (cnt > 0)
                {
                    printf("+");        // 如果不是第一次输出，前面加正号+
                }
                printf("x");
            }
            else if (pPoly[1] == -1)       // 如果系数==-1
            {
                printf("-x");
            }
            else
            {
                if (pPoly[1] > 0 && cnt > 0)        // 如果系数大于0，且不是第一次输出，前面加正号+
                {
                    printf("+");
                }
                printf("%dx", pPoly[1]);
            }
            cnt++;
        }
    }

    // 单独输出0次幂
    if (pPoly[0] != 0)
    {
        if (cnt > 0)
        {
            printf("+");        // 如果系数大于0，且不是第一次输出，需要前面加正号+
        }
        printf("%d", pPoly[0]);
        cnt++;
    }

    if (cnt == 0)
    {
        printf("0");
    }

    printf("\n");

    return cnt; // 返回输出的项数
}

// 两个多项式相加
//-----------------------------------------------------------------------------------------------
// 名称: void AddPolynomial(int *pPoly1, int *pPoly2, int n)
// 功能: 多项式相加
// 算法: 两个数组的下标相同的元素值相加
// 参数:
//      [int *pPoly1] --- 多项式1数组指针
//      [int *pPoly2] --- 多项式2数组指针
//      [int n] --- 数组长度
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void AddPolynomial(int *pPoly1, int *pPoly2, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        pPoly1[i] += pPoly2[i]; // 系数求和
    }
}
