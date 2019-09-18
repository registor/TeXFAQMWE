#include <stdio.h>
#include <stdlib.h>

// 求两个数的平均值的函数原型
void Average(double x, double y, double *pAvg);

//主函数
int main()
{
    double dfAvg;
    double x = 5.0, y = 6.0; /*声明变量*/

    Average(x, y, &dfAvg); /* 调用函数 */

    /*函数调用*/
    printf("Average of %f and %f is %f\n", x, y, 
                                         dfAvg);

    return 0;
}

// 求两个数的平均值的函数定义
/*函数头*/
void Average(double x, double y, double *pAvg)
{
    (*pAvg) =  (x + y) / 2.0;  /*函数体*/
}
