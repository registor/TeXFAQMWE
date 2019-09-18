#include <stdio.h>
#include <stdlib.h>

//原型可不指明形参名称
void Swap(int *, int *) ;

//主函数
int main()
{
    /*...*/
    /*函数调用*/
    Swap(&iVal1, &iVal2);
    /*...*/

    return 0;
}

// 交换两个数的函数定义
void Swap(int *px, int *py)
{
    int temp;  /*临时变量*/
    temp = *px;
    *px = *py;
    *py = temp;
}
