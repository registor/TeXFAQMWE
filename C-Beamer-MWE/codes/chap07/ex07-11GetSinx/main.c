/* 用泰勒公式实现计算sin的近似值*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义宏常量
#define epsilon 1e-10
// 定义const常量
const double pi=3.1415926;

// 函数原型
double GetSinx(double);

int main()
{
    printf("math sin(pi / 2) = %f\n", sin(pi / 2));
    printf("custom sin(pi / 2) = %f\n", GetSinx(pi / 2));

    printf("math sin(pi / 3) = %f\n", sin(pi / 3));
    printf("custom sin(pi / 3) = %f\n", GetSinx(pi / 3));

    return 0;
}

// 函数定义
double GetSinx(double x)
{
    double sum = x;  // 计算结果
    double x_pow = x; // x的幂
    double item = 0.0; // 累加项

    int n = 1; // 计数
    long long int fact = 1; // 阶乘
    int sign = 1; // 符号

    do
    {
        // 计算阶乘，在公式中作分母
        fact = fact * (n + 1) * (n + 2);
        // x_pow是x的幂，在公式中作分子
        x_pow *= x * x;
        // 当前项的符号
        sign = -sign;
        // 计算当前累加项
        item =  sign * x_pow / fact;
        // 累加
        sum += item;
        // 递增
        n += 2;
    }while(fabs(item) > epsilon);

    return sum;
}
