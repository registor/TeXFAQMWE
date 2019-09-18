#include <stdio.h>
#include <stdlib.h>

#define N 10

//函数原型
// 数组遍历
void Traversal(int *, int, void (*pf)(int *));
// 功能函数
void Input(int *);
void Output(int *);
void Set2Zero(int *);
void PowOdd(int *);

int main()
{
    int iArray[N];

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    Traversal(iArray, N, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    Traversal(iArray, N, Output);
    printf("\n");

    Traversal(iArray, N, PowOdd);
    // 把输出重定向到文件"out.txt"
    freopen("out.txt","w",stdout);
    Traversal(iArray, N, Output);
    printf("\n");
    // 把输出重定向到控制台
    freopen("CON","w",stdout);

    return 0;
}

// 函数定义
// 遍历数组
void Traversal(int *pa, int n, void (*pf)(int *))
{
    int *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

// 输入数据
void Input(int * pData)
{
    scanf("%d", pData);
}
// 输出数据
void Output(int * pData)
{
    // 输出
    printf("%d ", *pData);
}

// 清0
void Set2Zero(int * pData)
{
    *pData = 0; // 清0
}

// 奇数元素求平方
void PowOdd(int * pData)
{
    if(*pData % 2 != 0)
    {
        *pData *= *pData;
    }
}

