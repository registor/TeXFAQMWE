#include <stdio.h>
#include <stdlib.h>

//在函数原型中可以不指明形参名称
void Swap(int *, int *) ;

//主函数
int main()
{
    int iVal1 = 5, iVal2 = 6; /*声明变量*/

    printf("before: a = %d, b = %d\n", iVal1, iVal2);
    /*函数调用*/
    Swap(&iVal1, &iVal2);
    printf("after: a = %d, b = %d\n", iVal1, iVal2);

    return 0;
}

// 交换两个数的函数定义
void Swap(int *px, int *py)  /*函数头*/
{
    int temp;  /*临时变量*/
    temp = *px;
    *px = *py;
    *py = temp;
}
