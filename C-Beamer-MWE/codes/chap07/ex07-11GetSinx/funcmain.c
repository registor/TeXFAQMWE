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
    printf("%f\n", sin(pi / 2));
    printf("%f\n", GetSinx(pi / 2));

    printf("%f\n", sin(pi / 3));
    printf("%f\n", GetSinx(pi / 3));

    return 0;
}
