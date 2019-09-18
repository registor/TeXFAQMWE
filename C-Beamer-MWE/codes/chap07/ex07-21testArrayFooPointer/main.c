#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 宏定义
#define N 10
#define EPSILON  1e-6

// 类型定义
typedef int (*ProcFooType)(int, int);

// 函数原型
// 数组操作
void InitArray(int *, int);
void OutArray(int *, int);
void SetArray(int *, int, int);
void ProcArray(int *, int, int, ProcFooType);

// 基本运算
int Power(int, int); // 求幂
int Root(int, int); // 开方
int Scale(int, int); // 缩放

int main()
{
    int iArray[N];

    int *pa = iArray;

    InitArray(pa, N);
    OutArray(pa, N);

    SetArray(pa, 4, N);
    OutArray(pa, N);

    ProcArray(pa, 2, N, Power);
    OutArray(pa, N);

    ProcArray(pa, 2, N, Root);
    OutArray(pa, N);

    ProcArray(pa, 2, N, Scale);
    OutArray(pa, N);

    return 0;
}

// 函数定义

// 数组初始化
void InitArray(int *pa, int n)
{
    // 循环实现
    for(int i = 0; i < n; i++)
    {
        pa[i] = 0;
    }

//    // 直接内存操作
//    memset(pa, 0, n * sizeof(int));
}

// 输出数组
void OutArray(int *pa, int n)
{
    int i;
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", pa[i]);
    }
    // 最后一个数后无空格，添加'\n'
    printf("%d\n", pa[i]);

}

// 将数组所有元素设置为val
void SetArray(int *pa, int val, int n)
{
    // 循环实现
    for(int i = 0; i < n; i++)
    {
        pa[i] = val;
    }
}

void ProcArray(int *pa, int k, int n, ProcFooType pf)
{
    // 循环实现
    for(int i = 0; i < n; i++)
    {
        pa[i] = pf(pa[i], k);
    }
}

// 基本运算
// 求幂
int Power(int x, int k)
{
    int r = 1;

    for(int i = 1; i <= k; i++)
    {
        r = r * x;
    }
    return r;
}
// 开方
int Root(int x, int k)
{
    int r;

    double x_n = (double)x;
    double f = (double)Power(x_n, k) - (double)x;

    while(fabs(f) > EPSILON)
    {
        // 原函数当前值
        double fx_n = (double)Power(x_n, k) - (double)x;
        // 导函数当前值
        double dfx_n = (double)k * (double)Power(x_n, k - 1);

        // 牛顿迭代法更新
        x_n = x_n - fx_n / dfx_n;

        // 误差
        f = (double)Power(x_n, k) - (double)x;
    }

    r = (int)x_n; // 取整

    return r;
}
// 缩放
int Scale(int x, int k)
{
    return k * x;
}
