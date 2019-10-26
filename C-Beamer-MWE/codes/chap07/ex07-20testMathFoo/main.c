#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 宏定义
#define EPSILON 1e-6

// 函数声明
double GetPower(double, int); // 累乘求幂
double GetRootBi(double, int); // 二分法求开方
double GetRootNewton(double, int); // 牛顿法求开方

float InvSqrt(float); // 约翰·卡马克所发明的快速计算平方根的倒数

unsigned int GetFact(unsigned int); // 连乘法求阶乘

// 主函数中只负责测试
int main()
{
    double r, x;
    int n;

    x = 4.0;
    n = 2;

    // 测试累乘求幂函数
    r = GetPower(x, n);
    printf("%f^%d=%f\n", x, n, r);

    // 测试二分法求开方函数
    r = GetRootBi(x, n);
    printf("root^%d(%f)=%f\n", n, x, r);

    // 测试牛顿法求开方函数
    r = GetRootNewton(x, n);
    printf("root^%d(%f)=%f\n", n, x, r);

    // 测试连乘求阶乘函数
    n = 10;
    printf("InvSqrt = %f\n", InvSqrt(n));
    printf("pow = %f\n", pow(n, -0.5));

    // 测试约翰·卡马克所发明的快速计算平方根的倒数

    return 0;
}

// 函数定义

// 累乘求幂函数
double GetPower(double x, int n)
{
    double result = 1.0;

    int i;

    for(i = 0; i < n; i++)
    {
        result *= x;
    }

    return result;
}

// 二分法求开方函数
double GetRootBi(double x, int n)
{
    // 高低界
    double low = x > 1.0 ? 1.0 : x;
    double high = x >= 1.0 ? x : 1.0;

    // 二分中值
    double mid = (low + high) / 2.0;

    // 中值的n次幂
    double f = GetPower(mid, n);

    // 循环
    while(fabs(f - x) > EPSILON)
    {
        if(f > x)
        {
            high = mid; // 比x大，舍去高端
        }
        else
        {
            low = mid; // 比x小，舍去低端
        }
        mid = (low + high) / 2.0; // 折半

        f = GetPower(mid, n); // 中值的n次幂
    }

    return mid;
}

// 牛顿法求开方函数
double GetRootNewton(double x, int n)
{
    // 初值
    double x_n = x;
    // 计算
    double f = GetPower(x_n, n) - x;

    // 根据精度控制循环
    while(fabs(f) > EPSILON)
    {

        // 原函数当前值
        double fx_n = GetPower(x_n, n) - x;
        // 导函数当前值
        double dfx_n = n * GetPower(x_n, n - 1);
        // 牛顿迭代法更新
        x_n = x_n - fx_n / dfx_n;
        // 误差
        f = GetPower(x_n, n) - x;
    }

    return x_n;
}

// 连乘求阶乘函数
unsigned int GetFact(unsigned int n)
{
    unsigned int result = 1;

    // 0的阶乘是1
    if(n == 0)
    {
        return 1;
    }

    int i;
    for(i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

// 约翰·卡马克所发明的快速计算平方根的倒数
/*
这是一个传奇算法，此算法最早被认为是由约翰·卡马克所发明，
但后来的调查显示，该算法在这之前就于计算机图形学的硬件与软件领域有所应用。
它的速度要比标准的牛顿迭代法快上 4 倍，
而其中的关键是一行神秘的代码和一个莫名其妙的数字0x5f3759df。
普度大学的数学家Lomont觉得很好玩，
决定要研究一下卡马克弄出来的这个猜测值有什么奥秘。
Lomont也是个牛人，在精心研究之后从理论上也推导出一个最佳猜测值，
和卡马克的数字非常接近, 0x5f37642f。
卡马克真牛，他是外星人吗？传奇并没有在这里结束。
Lomont计算出结果以后非常满意，
于是拿自己计算出的起始值和卡马克的神秘数字做比赛，
看看谁的数字能够更快更精确的求得平方根。
结果是卡马克赢了...

谁也不知道卡马克是怎么找到这个数字的。
最后Lomont怒了，采用暴力方法一个数字一个数字试过来，
终于找到一个比卡马克数字要好上那么一丁点的数字，
虽然实际上这两个数字所产生的结果非常近似，
这个暴力得出的数字是0x5f375a86。
*/

// 注意该算法只能计算float类型的数据
float InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;       // get bits for floating value
    i = 0x5f3759df - (i >> 1); // gives initial guess y0
    x = *(float*)&i;         // convert bits back to float
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

    return x;
}
