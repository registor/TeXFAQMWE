/*--------------------------------------------------------------------------------
* Copyright (c) 2017,西北农林科技大学信息学院计算机科学系
* All rights reserved.
*
* 文件名称：main.c
* 文件标识：见配置管理计划书
* 摘要：常见递归函数的演示代码。
*
* 当前版本：1.0
* 作者：耿楠
* 完成日期：2018年11月09日
*
* 取代版本：无
* 原作者：
* 完成日期：
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // 需要C99/C11支持
#include <string.h>

#define N 1000
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

// 函数原型
int GetPower(int, int); // 计算整数的幂
unsigned int GetFact(unsigned int); // 计算阶乘
int GetGCD(int, int); // 辗转相除法求最大公约数的递归算法
int GetFibo(int);  // 递归求斐波那契(Fibonacci)数列
int GetArrSum(int [], int, int); // 求数组的和
int GetArrMax(int [], int, int); // 求数组的最大值
int GetArrMin(int [], int, int); // 求数组的最小值
bool IsPalindrome(char [], int); // 递归判断是否为回文
int YanghuiTri(int, int); // 用递归求杨辉三角形第n行，第k列的值C(n, k)
void Hanoi(int, char, char, char); // 用递归求解汉诺塔问题
int BiSearchRec(int *, int, int, int); // 用递归实现二分查找

int main()
{
    // 测试阶乘
    printf("Fact=%d\n", GetFact(10));

    // 测试最大公约数
    printf("GCD=%d\n", GetGCD(235, 786));

    // 测试整数的幂运算
    printf("Power=%d\n", GetPower(6, 3));

    // 测试斐波那契
    printf("Fibo=%d\n", GetFibo(7));

    // 判断是不是回文
    char *pstr = "abcba";
    if(IsPalindrome(pstr, strlen(pstr)))
    {
        printf("%s is Palindrome\n", pstr);
    }
    else
    {
        printf("%s is not Palindrome\n", pstr);
    }

    // 求数组的和
    int a[] = {1, 2, 3, 4, 5};
    int s = 0, e = 4;
    printf("ArrSum=%d\n", GetArrSum(a, s, e));

    // 求数组的和
    int b[] = {5, 1, 4, 6, 2};
    s = 0;
    e = 4;
    printf("ArrMax=%d\n", GetArrMax(b, s, e));
    printf("ArrMin=%d\n", GetArrMin(b, s, e));

    // 用递归求杨辉三角形第n行，第k列的值C(n, k)
    int c = YanghuiTri(6, 4);
    printf("C(%d, %d)=%d\n", 6, 4, c);

    // 测试汉诺塔
    printf("====Hanoi start====\n");
    Hanoi(3, 'A', 'C', 'B');
    printf("====Hanoi end====\n");

    // 测试折半查找
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int val = 9, low = 0, high = 9;
    printf("====BiSearch start====\n");
    printf("the %d pos = %d \n", val, BiSearchRec(arr, low, high, val));
    printf("====BiSearch end====\n");

    return 0;
}

// 函数定义

//-----------------------------------------------------------------------------------------------
// 名称: unsigned int GetFact(unsigned int n)
// 功能: 计算阶乘
// 算法: 通过递归计算阶乘
//          f(k) = k(f(k-1)。
// 参数:
//       [unsigned int n] --- 要计算的整数
// 返回: [unsigned int]  --- 返回阶乘计算结果
// 作者: 耿楠
// 日期: 2018年11月09日
//-----------------------------------------------------------------------------------------------
unsigned int GetFact(unsigned int n)
{
    if(n <= 1)
    {
        return 1; // 0和1的阶乘为1，结束条件
    }
    else
    {
        return n * GetFact(n - 1);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetGCD(int m, int n)
// 功能: 用求余实现辗转相除法
// 算法: 递归求解，设有两个整数m和n：
//          ① 求两个数m和n的余数rem；
//          ② 若余数rem为0，则较小数即为最大公约数；否则执行③；
//          ③ 用较小的数替换较大的数，用余数rem替换较小的数；
//          ④ 返回① .
// 参数:
//       [int m, int n] --- 第1个整数m
//       [int m, int n] --- 第2个整数n
// 返回: [int]  --- 返回m,n的最大公约数
// 作者: 耿楠
// 日期: 2018年11月09日
//-----------------------------------------------------------------------------------------------
int GetGCD(int m, int n)
{
    return n == 0 ? m : GetGCD(n, m % n);
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetPower(int x, int n)
// 功能: 计算幂
// 算法: 通过递归计算幂
//          x^n=x*x^(n - 1)。
// 参数:
//       [int x] --- 要计算整数x
//       [int n] --- 幂次n
// 返回: [int]  --- 返回幂运算结果
// 作者: 耿楠
// 日期: 2018年11月09日
//-----------------------------------------------------------------------------------------------
int GetPower(int x, int n)
{
    if(n == 0)
    {
        return 1;
    }
    else
    {
        return x * GetPower(x, n - 1);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetFibo(int n)
// 功能: 计算斐波那契数列
// 算法: 通过递归计算斐波那契数列
//          f(n) = f(n-1) + f(n-2)。
// 参数:
//       [int x] --- 要计算整数x
//       [int n] --- 幂次n
// 返回: [int]  --- 返回幂运算结果
// 作者: 耿楠
// 日期: 2018年11月09日
//-----------------------------------------------------------------------------------------------
int GetFibo(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return GetFibo(n - 1) + GetFibo(n - 2);
    }
}

// ---------------------------------------------------------------------------------------------- -
// 名称: bool IsPalindrome(char str[], int len)
// 功能: 判断是否为回文
// 算法: 通过递归判断是否为回文
//          ① 检查第一个和最后一个字符是否相同。
//          ② 在将第一个和最后一个字符删除之后，检查剩余的字符串是否仍是回文。
//          如果这两个条件都满足，那么该字符串就是回文。
// 参数:
//       [char str[]] --- 要判断的字符串指针
//       [int len] --- 字符串长度
// 返回: [bool]  --- 是返回真，否则返回假
// 作者: 耿楠
// 日期: 2018年11月09日
//-----------------------------------------------------------------------------------------------
bool IsPalindrome(char str[], int len)
{
    if(len <= 1)
    {
        return true;
    }
    else
    {
        return (str[0] == str[len - 1] && IsPalindrome(str + 1, len - 2 ));
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetArrSum(int pa[], int start, int end)
// 功能: 计算数列指定范围内数据的和
// 算法: 通过递归计算
//          f(a[0], a[1], ..., a[n-1]) = a[0] + f(a[1], a[2], ..., a[n-1])。
// 参数:
//       [int pa[]] --- 数组指针
//       [int start] --- 起始元素下标
//       [int end] --- 终止元素下标
// 返回: [int]  --- 返回求和运算结果
// 作者: 耿楠
// 日期: 2018年11月13日
//-----------------------------------------------------------------------------------------------
int GetArrSum(int pa[], int start, int end)
{
    if(start == end) //递归边界
    {
        return pa[start];
    }

    return pa[start] + GetArrSum(pa, start + 1, end); //递归公式
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetArrMax(int pa[], int start, int end)
// 功能: 求数列指定范围内数据的最大值
// 算法: 通过递归计算
//          max(a[0], a[1], ..., a[n-1]) = max(a[0], max(a[1], a[2], ..., a[n-1]))。
// 参数:
//       [int pa[]] --- 数组指针
//       [int start] --- 起始元素下标
//       [int end] --- 终止元素下标
// 返回: [int]  --- 返回最大值
// 作者: 耿楠
// 日期: 2018年11月13日
//-----------------------------------------------------------------------------------------------
int GetArrMax(int pa[], int start, int end)
{
    if(start == end) //递归边界1
    {
        return pa[start];
    }
    else if(start + 1 == end) //递归边界2
    {
        return max(pa[start], pa[end]);
    }
    else
    {
        return max(pa[start], GetArrMax(pa, start + 1, end));   //递归公式!!!
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int GetArrMin(int pa[], int start, int end)
// 功能: 求数列指定范围内数据的最小值
// 算法: 通过递归计算
//          min(a[0], a[1], ..., a[n-1]) = min(a[0], min(a[1], a[2], ..., a[n-1]))。
// 参数:
//       [int pa[]] --- 数组指针
//       [int start] --- 起始元素下标
//       [int end] --- 终止元素下标
// 返回: [int]  --- 返回最大值
// 作者: 耿楠
// 日期: 2018年11月13日
//-----------------------------------------------------------------------------------------------
int GetArrMin(int pa[], int start, int end)
{
    if(start == end) //递归边界1
    {
        return pa[start];
    }
    else if(start + 1 == end) //递归边界2
    {
        return min(pa[start], pa[end]);
    }
    else
    {
        return min(pa[start], GetArrMin(pa, start + 1, end));   //递归公式!!!
    }
}


//-----------------------------------------------------------------------------------------------
// 名称: int YanghuiTri(int n, int k)
// 功能: 求杨辉三解形第n行，第k列的值C(n, k)
// 算法: 求杨辉三解形第n行，第k列的值C(n, k):
//          C(n, k)=n!/(k!*(n-k)!)
//          C(n, k)的值能够按照几何来排成一个三角形，其中n从上向下递增，k从右向右递增。
//          该三角形又称为杨辉三角形(早)帕斯卡三角形(晚)，如：
//                                      C(0, 0)
//                               C(1, 0)    C(1, 1)
//                        C(2, 0)    C(2, 1)    C(2, 2)
//                 C(3, 0)    C(3, 1)    C(3, 2)   C(3, 3)
//          C(4, 0)    C(4, 1)    C(4, 2)    C(4, 3)    C(4,4)
//          杨辉三角形一个有趣的特性就是除了在左右两个边缘的数字总是1之外，每一个数
//          字是它上面的两个数字的和。例如：
//                              1
//                           1    1
//                       1     2      1
//                   1     3       3     1
//               1    4       6      4    1
//            1    5     10    10    5     1
//          1   6    15    20    15    6    1
// 参数:
//       [int n] --- 杨辉三解形行数n
//       [int k] --- 杨辉三解形列数k
// 返回: [int]  --- 返回C(n, k)
// 作者: 耿楠
// 日期: 2018年11月13日
//-----------------------------------------------------------------------------------------------
int YanghuiTri(int n, int k)
{
    if (n == k)
    {
        return 1;
    }
    if (k == 0)
    {
        return 1;
    }
    if (k == 1)
    {
        return n;
    }
    if (n == 1)
    {
        return 1;
    }
    return YanghuiTri(n - 1, k - 1) + YanghuiTri(n - 1, k);
}

//-----------------------------------------------------------------------------------------------
// 名称: void Move(int n, char start, char finish)
// 功能: 输出汉诺塔操作中1个盘子的移动
// 算法: 简单printf()输出。
// 参数:
//       [int n] --- 盘子编号
//       [char start] --- 移动起始塔座
//       [char finish] --- 移动目标塔座
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月14日
//-----------------------------------------------------------------------------------------------
void Move(int n, char start, char finish)
{
    printf("the %dth plate from %c to %c\n", n, start, finish);
}

//-----------------------------------------------------------------------------------------------
// 名称: void Hanoi(int n, char start, char finish, char temp)
// 功能: 将n个盘子从start塔座移到finish塔座的过程(借助temp塔座)
// 算法: 递归求解，设有n个盘子：
//         ① 把上面的n-1只圆盘从起始座移到临时座上。
//         ② 把剩下的惟一的圆盘从起始座移到目标座上。
//         ③ 把n-1只圆盘组成的盘塔从临时座上移回到目标座上。
// 参数:
//       [int n] --- 盘子总数
//       [char start] --- 起始塔座标记
//       [char finish] --- 目标塔座标记
//       [char temp] --- 临时塔座标记
// 返回: [void]  --- 无
// 作者: 耿楠
// 日期: 2018年11月14日
//-----------------------------------------------------------------------------------------------
void Hanoi(int n, char start, char finish, char temp)
{
    if(n == 1)
    {
        Move(n, start, finish);
    }
    else
    {
        Hanoi(n - 1, start, temp, finish);
        Move(n, start, finish);
        Hanoi(n - 1, temp, finish, start);
    }
}

//-----------------------------------------------------------------------------------------------
// 名称: int BiSearchRec(int *pa, int low, int high, int key)
// 功能: 用递归实现二分查找
// 参数:
//       [int *pa] --- 数组指针
//       [int low] --- 需要查找的起始下标
//       [int high] --- 需要查找的结束下标
//       [int key] --- 要查找的值
// 返回: [int]  --- 查找到的下标，若找不到，返回-1
// 作者: 耿楠
// 日期: 2018年11月14日
// 注意: 要求被查找的数组有序
//-----------------------------------------------------------------------------------------------
int BiSearchRec(int *pa, int low, int high, int key)
{
    int mid; // 声明折半下标
    if(low > high)
    {
        return -1; // 没有找到
    }
    else
    {
        mid = (high + low) / 2; // 折半
        if(pa[mid] == key)
        {
            return mid; // 找到，返回下标
        }
        else if(pa[mid] > key) // 当前值大于k
        {
            return BiSearchRec(pa, low, mid - 1, key); // 在下半部查找
        }
        else // 当前值小于k
        {
            return BiSearchRec(pa, mid + 1, high, key);  // 在上半部查找
        }
    }
}
