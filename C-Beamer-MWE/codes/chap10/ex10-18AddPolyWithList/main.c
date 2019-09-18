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
typedef struct Node
{
    int coef; // 系数成员
    int exp;   // 幂次成员
    struct Node *next; // 指针域成员
} PolyNode, * Polynomial;

// 函数原型
Polynomial InitPolynomial(); // 初始化多项式
void CreatePolynomial(Polynomial); // 输入多项式
void InsertPolyNode(int, int, Polynomial); // 插入多项式一个节点(一项)
int OutputPolynomial(Polynomial); // 输出多项式
Polynomial AddPolynomial(Polynomial, Polynomial); // 两个多项式相加
void DestroyList(Polynomial *); // 销毁多项式

// 测试
int main()
{
    Polynomial p1, p2;
    Polynomial PolySum;

    // 输入并输出多项式1
    p1 = InitPolynomial();
    CreatePolynomial(p1);
    //OutputPolynomial(p1);

    // 输入并输出多项式2
    p2 = InitPolynomial();
    CreatePolynomial(p2);
    //OutputPolynomial(p2);

    PolySum = AddPolynomial(p1, p2);
    OutputPolynomial(PolySum);

    DestroyList(&PolySum); // 求加合并后原多项式不需要再释放

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: Polynomial InitPolynomial()
// 功能: 初始化多项式
// 算法: 分配一个内存空间作为多项式中的头结点(哑元结点)
// 参数:
//      无
// 返回: [Polynomial]  --- PolyNode类型的指针
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
Polynomial InitPolynomial()
{
    Polynomial p;

    // 创建节点
    p = (Polynomial)malloc(sizeof(PolyNode));
    if (!p)
    {
        printf("Not enough memory!\n");
        return NULL; // 内存分配失败
    }

    p->next = NULL; // 指针域赋NULL

    return p;
}

//-----------------------------------------------------------------------------------------------
// 名称: void DestroyList(Polynomial *pHead)
// 功能: 销毁多项式
// 算法: 通过销毁链表销毁多项式
// 参数:
//      [Polynomial *pHead] --- 表达多项式的链表头结点的指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void DestroyList(Polynomial *pHead)
{
    Polynomial p;

    while(*pHead != NULL)
    {
        p = (*pHead)->next; // 空出当前结点
        free(*pHead); // 销毁当前结点
        *pHead = p; // 下一个结点
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: void InsertPolyNode(int c, int e, Polynomial pHead)
// 功能: 为多项式一个结点
// 算法: 按幂次降序插入
// 参数:
//      [int c] --- 多项式结点系数值
//      [int e] --- 多项式结点幂次值
//      [Polynomial pHead] --- 表达多项式的链表头结点的指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void InsertPolyNode(int c, int e, Polynomial pHead)
{
    Polynomial cur, prev, p;

    p = (Polynomial)malloc(sizeof(PolyNode)); // 分配空间
    if (!p)
    {
        printf("Not enough memory!\n"); // 分配失败
        return;
    }

    // 赋值
    p->coef = c; // 系数成员
    p->exp = e;  // 幂次成员


    // 搜索插入位置
    cur = pHead->next; // 绕过头结点
    prev = NULL;

    while(cur != NULL && p->exp < cur->exp) // 幂次降序插入
    {
        prev = cur;
        cur = cur->next;
    }

    if(cur != NULL && p->exp == cur->exp) // 结点已存在
    {
        cur->coef += p->coef; // 系数累加
        free(p);
        return;
    }

    if(prev == NULL) // 前驱节点为空，将其指向头节点
    {
        prev = pHead;
    }

    // 插入结点
    p->next = prev->next;
    prev->next = p;
}

//-----------------------------------------------------------------------------------------------
// 名称: void CreatePolynomial(Polynomial pHead)
// 功能: 为多项式一个结点
// 算法: 按幂次降序通过插入节点创建多项式
// 参数:
//      [Polynomial pHead] --- 表达多项式的链表头结点的指针
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
void CreatePolynomial(Polynomial pHead)
{
    int e = 0, c = 0;

    // 至少要输入1次，用do...while循环实现
    do
    {
        scanf("%d %d", &e, &c);
        InsertPolyNode(c, e, pHead); // 插入
    }
    while (e != 0);
}

//-----------------------------------------------------------------------------------------------
// 名称: int OutputPolynomial(Polynomial pHead)
// 功能: 输出多项式
// 算法: 遍历链表，将系数不为0的结点按要求输出
// 参数:
//      [Polynomial pHead] --- 表达多项式的链表头结点的指针
// 返回: [int]  --- 返回输出的项数
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
int OutputPolynomial(Polynomial pHead)
{
    int cnt = 0;

    Polynomial p = pHead->next;

    // 输出多项式
    while(p != NULL)
    {
        if(p->exp != 1 && p->exp != 0)
        {
            if (p->coef != 0)        // 只输出系数不为0的项
            {
                if (p->coef == 1)        // 如果系数==1，比如40 1
                {
                    if (cnt > 0)                // 如果不是第一次输出，则前面加正号+
                    {
                        printf("+");
                    }
                    printf("x%d", p->exp);        // 输出x40
                }
                else if (p->coef == -1)        // 如果系数==-1，比如40 -1
                {
                    printf("-x%d", p->exp);        // 前面加负号-，系数-1省略，输出-x40
                }
                else        // 其他情况，系数不等于1，也不等于-1
                {
                    if (p->coef < 0)
                    {
                        printf("%dx%d", p->coef, p->exp);        // 系数小于0，直接输出
                    }
                    else
                    {
                        if (cnt > 0)
                        {
                            printf("+");        // 如果系数大于0，且不是第一次输出，需要前面加正号+
                        }
                        printf("%dx%d", p->coef, p->exp);
                    }
                }
                cnt++;
            }
        }
        else if(p->exp == 1) // 单独输出1次幂
        {
            if (p->coef != 0)        // 系数不等于0
            {
                {
                    if (p->coef == 1)        // 如果系数==1
                    {
                        if (cnt > 0)
                        {
                            printf("+");        // 如果输出超过一次，前面加正号+
                        }
                        printf("x");
                    }
                    else if (p->coef == -1)        // 如果系数==-1
                    {
                        printf("-x");
                    }
                    else
                    {
                        if (p->coef > 0 && cnt > 0)        // 如果系数大于0，且不是第一次输出，前面加正号+
                        {
                            printf("+");
                        }
                        printf("%dx", p->coef);
                    }
                    cnt++;
                }
            }
        }
        else
        {
            // 单独输出0次幂
            if (p->coef != 0)
            {
                if (cnt > 0)
                {
                    printf("+");        // 如果系数大于0，且不是第一次输出，需要前面加正号+
                }
                printf("%d", p->coef);
                cnt++;
            }
        }
        p = p->next;
    }
    return cnt; // 返回输出的项数
}

//-----------------------------------------------------------------------------------------------
// 名称: Polynomial AddPolynomial(Polynomial p1, Polynomial p2)
// 功能: 输出多项式
// 算法: 采用链表归并的算法，将两个链表进行归并操作
// 参数:
//      [Polynomial p1] --- 第1个多项式链表头结点指针
//      [Polynomial p2] --- 第2个多项式链表头结点指针
// 返回: [Polynomial]  --- 返回结果多项式链表头结点的指针
// 作者: 耿楠
// 日期: 2018年12月11日
//-----------------------------------------------------------------------------------------------
Polynomial AddPolynomial(Polynomial p1, Polynomial p2)
{
    Polynomial pa, pb, pc, Lc, p;
    pa = p1->next;
    pb = p2->next;
    Lc = pc = p1;   // 用pa的头结点作为Lc的头结点

    while(pa && pb)
    {
        if(pa->exp > pb->exp)
        {
            pc->next = pa;             //如果指数不相等，pc指针连上指数大的结点，
            pc = pa;
            pa = pa->next;             //指向该结点的指针后移
        }
        else if(pa ->exp < pb->exp)
        {
            pc->next = pb;               //pc指针连上指数小的结点，
            pc = pb;
            pb = pb->next;               //指向该结点的指针后移
        }
        else
        {
            pa->coef = pa->coef + pb->coef;     //指数相等时，系数相加
            pc->next = pa;
            pc = pa;
            pa = pa->next;             //两指针都往后移
            p = pb;
            pb = pb->next;
            free(p);
        }
    }

    pc->next = pa ? pa : pb; // 插入剩余段

    return Lc; // 返回头结点
}
