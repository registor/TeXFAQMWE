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
#define MAXDEG 100

/*定义多项式结构*/
typedef struct
{
    int CoeffArray[MAXDEG + 1]; // 系数数组成员
    int HighPower; // 最高幂次成员
} Polynomial;

// 函数原型
void InitPolynomial(Polynomial *); // 初始化多项式
void InputPolynomial(Polynomial *); // 输入多项式
int OutputPolynomial(Polynomial *); // 输出多项式
void AddPolynomial(Polynomial *, const Polynomial *, const Polynomial *); // 两个多项式相加

int main()
{
    Polynomial Poly1, Poly2;
    Polynomial PolySum;

    // 输入并输出多项式1
    InputPolynomial(&Poly1);
    // OutputPolynomial(&Poly1);

    // 输入并输出多项式2
    InputPolynomial(&Poly2);
    //OutputPolynomial(&Poly2);

    // 求和，并将结果存储在多项式1后输出结果
     AddPolynomial(&PolySum, &Poly1, &Poly2);
     OutputPolynomial(&PolySum);

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: void InitPolynomial(Polynomial *pPoly)
// 功能: 初始化多项式，将各幂次系数初始化为0
// 算法: 用结构体数组成员下标表示幂次，将对应元素置0
// 参数:
//      [Polynomial *pPoly] --- 表达多项式的结构体指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void InitPolynomial(Polynomial *pPoly)
{
    int i;

    for (i = 0; i <= MAXDEG; i++)
    {
        pPoly->CoeffArray[i] = 0; // 系数赋0
    }

    pPoly->HighPower = 0; // 最高幂次赋0
}

//-----------------------------------------------------------------------------------------------
// 名称: void InputPolynomial(Polynomial *pPoly)
// 功能: 输入多项式
// 算法: 用结构体数组成员的下标表示幂次，将对应元素置为系数
// 参数:
//      [Polynomial *pPoly] --- 表达多项式的结构体指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void InputPolynomial(Polynomial *pPoly)
{
    int power = 0, coeff = 0;

    InitPolynomial(pPoly);

    // 至少要输入1次，用do...while循环实现
    do
    {
        scanf("%d %d", &power, &coeff);
        pPoly->CoeffArray[power] = coeff;
        if (pPoly->HighPower < power) // 记录最大幂次
        {
            pPoly->HighPower = power;
        }
    }while (power != 0);
}

//-----------------------------------------------------------------------------------------------
// 名称: void AddPolynomial(Polynomial *pPolyResult, const Polynomial *pPoly1, const Polynomial *pPoly2)
// 功能: 多项式相加
// 算法: 用结构体数组成员的下标表示幂次，将对应元素置为系数
// 参数:
//      [Polynomial *pPolyResult] --- 结果多项式的结构体指针
//      [Polynomial *pPoly1] --- 相加多项式1的结构体指针
//      [Polynomial *pPoly2] --- 相加多项式2的结构体指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void AddPolynomial(Polynomial *pPolyResult, const Polynomial *pPoly1, const Polynomial *pPoly2)
{
    int i;

    InitPolynomial(pPolyResult); // 初始化结果多项式

    // 确定最高幂次
    if (pPoly1->HighPower < pPoly2->HighPower)
    {
        pPolyResult->HighPower = pPoly2->HighPower;
    }
    else
    {
        pPolyResult->HighPower = pPoly1->HighPower;
    }

    // 对应系数相加
    for (i = pPolyResult->HighPower; i >= 0; i--)
    {
        pPolyResult->CoeffArray[i] = pPoly1->CoeffArray[i] + pPoly2->CoeffArray[i];
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int OutputPolynomial(Polynomial *pPoly)
// 功能: 输出多项式
// 算法: 用结构体数组成员的下标表示幂次，其值做为系数输出
// 参数:
//      [Polynomial *pPoly] --- 表达多项式的结构体指针
// 返回: [int]  --- 输出的多项式项数
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
int OutputPolynomial(Polynomial *pPoly)
{
    int i;

    int cnt = 0;

    // 输出2次幂及其以前的项(1次幂和0次幂需要单独处理)
    for (i = pPoly->HighPower; i > 1; i--)
    {
        if (pPoly->CoeffArray[i] != 0)        // 只输出系数不为0的项
        {
            if (pPoly->CoeffArray[i] == 1)        // 如果系数==1，比如40 1
            {
                if (cnt > 0)                // 如果不是第一次输出，则前面加正号+
                {
                    printf("+");
                }
                printf("x%d", i);        // 输出x40
            }
            else if (pPoly->CoeffArray[i] == -1)        // 如果系数==-1，比如40 -1
            {
                printf("-x%d", i);        // 前面加负号-，系数-1省略，输出-x40
            }
            else        // 其他情况，系数不等于1，也不等于-1
            {
                if (pPoly->CoeffArray[i] < 0)
                {
                    printf("%dx%d", pPoly->CoeffArray[i], i);        // 系数小于0，直接输出
                }
                else
                {
                    if (cnt > 0)
                    {
                        printf("+");        // 如果系数大于0，且不是第一次输出，需要前面加正号+
                    }
                    printf("%dx%d", pPoly->CoeffArray[i], i);
                }
            }
            cnt++;
        }
    }

    // 单独输出1次幂
    if (pPoly->CoeffArray[1] != 0)        // pPoly[1]的系数不等于0
    {
        {
            if (pPoly->CoeffArray[1] == 1)        // 如果系数==1
            {
                if (cnt > 0)
                {
                    printf("+");        // 如果输出超过一次，前面加正号+
                }
                printf("x");
            }
            else if (pPoly->CoeffArray[1] == -1)        // 如果系数==-1
            {
                printf("-x");
            }
            else
            {
                if (pPoly->CoeffArray[1] > 0 && cnt > 0)        // 如果系数大于0，且不是第一次输出，前面加正号+
                {
                    printf("+");
                }
                printf("%dx", pPoly->CoeffArray[1]);
            }
            cnt++;
        }
    }

    // 单独输出0次幂
    if (pPoly->CoeffArray[0] != 0)
    {
        if (cnt > 0)
        {
            printf("+");        // 如果系数大于0，且不是第一次输出，需要前面加正号+
        }
        printf("%d", pPoly->CoeffArray[0]);
        cnt++;
    }

    if (cnt == 0)
    {
        printf("0");
    }

    printf("\n");

    return cnt; // 返回输出的项数
}
