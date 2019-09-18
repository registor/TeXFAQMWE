#include <stdio.h>
#include <stdlib.h>

// 求两个数的平均值
double Average(double x, double y)  /*函数头*/
{
    return (x + y) / 2.0;  /*函数体*/
}

//主函数
int main()
{
    double x = 5.0, y = 6.0; /*声明变量*/

    /*函数调用*/
    printf("Average of %f and %f is %f\n", x, y, Average(x, y));

    return 0;
}
