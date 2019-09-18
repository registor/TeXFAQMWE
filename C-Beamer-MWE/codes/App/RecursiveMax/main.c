/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：演示采用递归查找数组最大值的不同实现方法。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2017年11月18日
*
* 取代版本：无
* 原作者：耿楠
* 完成日期：2017年11月18日
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

// 全局变量
int glMax, glMin;

// 数组遍历函数原型
void Traversal(int *, int, void (*pf)(int *));
void RandArray(int *, int);
// 数组遍历功能函数
void Input(int *);
void Output(int *);

// 求最大值函数原型
int GetMax(int, int);

int PreRecursiveMaxWithSize(int *, int); // 前向递归，传入数组长度
int PreRecursiveMaxCom(int *, int); // 前向递归，传入数组长度，采用复合语句
int PreRecursiveMaxContIf(int *, int); // 前向递归，传入数组长度，递归结束在else分支
int PreRecursiveMaxByPt(int *, int); // 前向递归，传入数组长度，通过指针操作数组元素
int PreRecursiveMaxWithIndex(int *, int); // 前向递归，传入最后一个元素下标索引
int PreRecursiveMaxWithInit(int *, int, int); // 前向递归，传入数组最后一个元素下标索引，并用数组的某个元素做为最大值初值
int PreRecursiveMaxByIdx0(int *, int); // 前向递归，传入数组长度，用pa[0]记录最大值
int PreRecursiveMaxDynamicIdx0(int *, int); // 前向递归，传入数组长度，根据情况舍弃pa[0]以缩短数组长度
int PreRecursiveMaxWithNothing(int *, int); // 前向递归，传入数组长度，不改变数组内容，且不使用额外变量
void PreRecursiveMaxWithGlobal(int *, int); // 前向递归，传入数组长度，使用全局变量
int BiRecursiveMax(int *, int); // 二分法递归，传入数组长度
int PostRecursiveMax(int *, int, int); // 后向递归，传入数组长度和起始元素下标索引，
void BiRecursiveMaxMinWithPt(int *, int, int, int*, int*); // 二分法递归求最大最小值

int main()
{
    int iArray[N];
    int iMax, iMin;

    // 产生随机数组元素值
    RandArray(iArray, N);
    // 输出数组中的各元素
    Traversal(iArray, N, Output);
    printf("\n");

    iMax = PreRecursiveMaxWithSize(iArray, N);
    printf("MaxWithSize=%d\n", iMax);

    iMax = PreRecursiveMaxCom(iArray, N);
    printf("MaxWithCom=%d\n", iMax);

    iMax = PreRecursiveMaxContIf(iArray, N);
    printf("MaxContIf=%d\n", iMax);

    iMax = PreRecursiveMaxByPt(iArray, N);
    printf("MaxByPt=%d\n", iMax);

    iMax = PreRecursiveMaxWithIndex(iArray, N - 1);
    printf("MaxWithIndex=%d\n", iMax);

    iMax = PreRecursiveMaxWithInit(iArray, N - 1, iArray[0]);
    printf("MaxWithInit=%d\n", iMax);

    iMax = PreRecursiveMaxByIdx0(iArray, N);
    printf("MaxByIdx0=%d\n", iMax);

    iMax = PreRecursiveMaxDynamicIdx0(iArray, N);
    printf("MaxDynamicIdx0=%d\n", iMax);

    iMax = PreRecursiveMaxWithNothing(iArray, N);
    printf("MaxWithNothing=%d\n", iMax);

    PreRecursiveMaxWithGlobal(iArray, N);
    printf("MaxWithGlobal=%d\n", glMax);

    iMax = BiRecursiveMax(iArray, N);
    printf("MaxBiMax=%d\n", iMax);

    iMax = PostRecursiveMax(iArray, N, 0);
    printf("MaxPostMax=%d\n", iMax);

    BiRecursiveMaxMinWithPt(iArray, 0, N - 1, &iMax, &iMin);
    printf("MaxBiMaxMin=%d, MinBiMaxMin=%d\n", iMax, iMin);

    return 0;
}

//-----------------------------------------------------------------------------------------------
// 名称：void Traversal(int *pa, int n, void (*pf)(int *))
// 功能：遍历数组
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
//       [void (*pf)(int *)] --- 处理元素的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
void Traversal(int *pa, int n, void (*pf)(int *))
{
    int *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void Input(int * pData)
// 功能：用scanf从stdin流读入一个数据
// 参数：
//       [int *pData] --- 需要存储的变量的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
void Input(int * pData)
{
    scanf("%d", pData);
}
//-----------------------------------------------------------------------------------------------
// 名称：void Output(int * pData)
// 功能：用printf向stdout流输出一个
// 参数：
//       [int *pData] --- 需要输出变量的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
void Output(int * pData)
{
    // 输出
    printf("%d ", *pData);
}

//-----------------------------------------------------------------------------------------------
// 名称：void RandArray(int * pa, int n)
// 功能：用随机数为数组各元素赋值
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
void RandArray(int * pa, int n)
{
    int i;
    // 置随机种子
    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        pa[i] = rand() % 100; // 生成[0, 100)之间的随机数
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int GetMax(int a, int b)
// 功能：返回两个数中的最大数
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
//       [void (*pf)(int *)] --- 处理元素的函数指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int GetMax(int a, int b)
{
    return (a > b) ? a : b;
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxWithSize(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxWithSize(int *pa, int n)
{
    int max1, max2; // 中间变量

    if (n == 1) // 注意，1表示数组中有1个元素
    {
        // 递归结束条件成立，结束递归，返回最大值
        return pa[0];
    }
    else
    {
        // 递归结束条件不成立，继续递归
        // 求a[0],a[1],...,a[n-2]的最大值max1
        max1 = PreRecursiveMaxWithSize(pa, n - 1);
        // 求max1和a[n-1]的最大值
        max2 = GetMax(max1, pa[n - 1]);

        return max2;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxCom(int* pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          将递归调用过程与比较两个数操作合并。
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxCom(int* pa, int n)
{
    if (n == 1) // 注意，1表示数组中有1个元素
    {
        return pa[0]; // 结束递归
    }

    // 复合调用
    return GetMax(PreRecursiveMaxCom(pa, n - 1), pa[n - 1]);
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxContIf(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          将递归结束分支置于if else的else分支中。
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxContIf(int *pa, int n)
{
    if (n > 1) // 元素个数大于1，继续递归
    {
        return GetMax(pa[n - 1], PreRecursiveMaxContIf(pa, n - 1));
    }
    else
    {
        return *pa; // 结束递归
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxByPt(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          通过指针的偏移访问数组中的元素
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxByPt(int *pa, int n)
{
    int max = 0;

    if(n == 1) // 注意，1表示数组中有1个元素
    {
        return *pa; // 结束递归
    }
    else
    {
        max = PreRecursiveMaxByPt(pa, n - 1); // 递归

        if(*(pa + n - 1) > max)
        {
            max = *(pa + n - 1);
        }

        return max;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxWithIndex(int *pa, int highest_index)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
// 参数：
//       [int *pa] --- 数组指针
//       [int highest_index] --- 数组的最大下标索引
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxWithIndex(int *pa, int highest_index)
{
    int max;

    if(!highest_index) // n == 0时结束递归
    {
        return pa[highest_index];
    }

    // 求a[0],a[1],...,a[n-1]的最大值max */
    max = PreRecursiveMaxWithIndex(pa, highest_index - 1);
    return pa[highest_index] > max ? pa[highest_index] : max; // ？号运算符
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxWithInit(int *pa, int highest_index, int num)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          通过传入一个值作为最大值的初值
// 参数：
//       [int *pa] --- 数组指针
//       [int highest_index] --- 数组的最大下标索引
//       [int num] --- 最大值初值，常用数组的第0个元素值作为初值
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxWithInit(int *pa, int highest_index, int num)
{
    if (highest_index == 0) // 结束递归
    {
        return num;
    }

    if (num < pa[highest_index])
    {
        num = pa[highest_index]; // 更新最大值
        return PreRecursiveMaxWithInit(pa, highest_index - 1, num); // 递归
    }
    else
    {
        return PreRecursiveMaxWithInit(pa, highest_index - 1, num); // 递归
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxByIdx0(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          默认pa[0]为最大值，递归过程中会更新，因此递归结束后，数组的内容会改变
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxByIdx0(int *pa, int n)
{
    if(n == 1)// 注意，1表示数组中有1个元素
    {
        return pa[0]; // 结束递归
    }
    else
    {
        if(pa[0] < pa[n - 1])
        {
            pa[0] = pa[n - 1]; // 更新pa[0]
        }

        return(PreRecursiveMaxByIdx0(pa, n - 1)); // 递归
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxDynamicIdx0(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          动态递归：分解数组时根据情况舍弃pa[0](pa + 1)
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxDynamicIdx0(int *pa, int n)
{
    if (n == 1) // 注意，1表示数组中有1个元素
    {
        return pa[0]; // 结束递归
    }

    n--; // 递归准备
    // 如果(pa[0] < pa[n])，则舍弃pa[0](pa[0] < pa[n]是1，比较隐晦，不建议使用)
    return PreRecursiveMaxDynamicIdx0(pa + (pa[0] < pa[n]), n); // 递归
}

//-----------------------------------------------------------------------------------------------
// 名称：int PreRecursiveMaxWithNothing(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          递归要求:
//              不能够改变数组的值
//              不能够使用另外的变量
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PreRecursiveMaxWithNothing(int *pa, int n)
{
    if (n == 1) // 注意，1表示数组中有1个元素
    {
        return pa[0]; // 结束递归
    }
    else
    {
        // 递归
        return (pa[n - 1] > PreRecursiveMaxWithNothing(pa, n - 1)) ?
               pa[n - 1] :
               PreRecursiveMaxWithNothing(pa, n - 1);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void PreRecursiveMaxWithGlobal(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          前向递归：a[0],a[1],...,a[n-2]中的最大值与a[n-1]比较大小
//          用全局变量实现。
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
void PreRecursiveMaxWithGlobal(int *pa, int n)
{
    if (n == 1) // 注意，1表示数据中有1个元素
    {
        // 递归结束条件成立，结束递归
        glMax = pa[0];
        return;
    }
    else
    {
        // 递归结束条件不成立，继续递归
        glMax = PreRecursiveMaxWithSize(pa, n - 1); // 求a[0],a[1],...,a[n-2]的最大值 */
        // 求glMax和a[n-2]的最大值
        glMax = GetMax(glMax, pa[n - 1]);
        return;
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：int BiRecursiveMax(int *pa, int n)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//          二分法思想：a[0],...,a[n / 2]中的最大值与a[n / 2],...a[n-1]中的最大值比较大小
// 参数：
//       [int *pa] --- 数组指针
//       [int n] --- 数组长度
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int BiRecursiveMax(int *pa, int n)
{
    if (n <= 1) // 注意，1表示数据中有1个元素
    {
        return pa[0]; // 结束递归
    }

    return GetMax(BiRecursiveMax(pa, n / 2), BiRecursiveMax(pa + n / 2, n / 2)); // 二分递归
}

//-----------------------------------------------------------------------------------------------
// 名称：int PostRecursiveMax(int *pa, int len, int start_index)
// 功能：采用分治思想，使用递归找一个数组中元素的最大值
//            后向递归：a[0]最大值与a[1],...,a[n-1]之间的最大值比较
// 参数：
//       [int *pa] --- 数组指针
//       [int len] --- 数组长度
//       [int start_index] --- 起始索引位置
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
int PostRecursiveMax(int *pa, int len, int start_index)
{
    if(start_index == len) // 满足递归条件
    {
        return pa[len - 1]; //结束递归
    }
    else
    {
        // 递归
        return GetMax(pa[start_index], PostRecursiveMax(pa, len, start_index + 1));
    }
}

//-----------------------------------------------------------------------------------------------
// 名称：void BiRecursiveMaxMinWithPt(int *pa, int left, int right, int *pMax, int *pMin)
// 功能：采用分治思想，使用递归找最大值和最小值，最大值和最小值分别通过指针传递地址
//          二分法思想：a[0],...,a[mid]中的最大值与a[mid],...a[n-1]中的最大值比较大小
// 参数：
//       [int *pa] --- 数组指针
//       [int left] --- 数组最低位置元素索引
//       [int right] --- 数组最高位置元素索引
//       [int *pMax] --- 存储最大值变量的指针
//       [int *pMin] --- 存储最小值变量的指针
// 返回：无
// 作者：耿楠
// 日期：2017年11月18日
//-----------------------------------------------------------------------------------------------
void BiRecursiveMaxMinWithPt(int *pa, int left, int right, int *pMax, int *pMin)
{
    if(left == right) // 只有1个元素，结束递归
    {
        *pMax = pa[left]; // 取得最大值
        *pMin = pa[left]; // 取得最小值
        return ;
    }
    else if((left + 1) == right) // 只有两个元素，结束递归
    {
        *pMax = pa[left] > pa[right] ? pa[left] : pa[right]; // 最大值
        *pMin = pa[left] > pa[right] ? pa[right] : pa[left]; // 最小值
        return ;
    }
    else
    {
        int mid = (left + right) / 2; // 折半

        int leftMax, leftMin, rightMax, rightMin; // 临时量

        BiRecursiveMaxMinWithPt(pa, left, mid, &leftMax, &leftMin); // 递归找出左边的最大最小值
        BiRecursiveMaxMinWithPt(pa, mid, right, &rightMax, &rightMin); // 递归找出右边的最大最小值

        *pMax = (leftMax > rightMax) ? leftMax : rightMax; // 左右两边最大值相比较，取最大的
        *pMin = (leftMin < rightMin) ? leftMin : rightMin; // 左右两边最小值相比较，取最小的

        return;
    }
}
