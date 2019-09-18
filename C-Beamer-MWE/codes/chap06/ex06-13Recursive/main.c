#include <stdio.h>
#include <stdlib.h>
//函数原型,
int Fact(int);
int main()
{
    printf("%d\n", Fact(3));

    return 0;
}
//函数定义
// 递归计算n!
int Fact(int n)
{
    // 简单情况
    if(n <= 1)
    {
        return 1;
    }
    else
    {
        //递归调用，分而治之
        return n * Fact(n - 1);
    }
}
//以Fact(3)为例，其实现过程可以理解为
/**
Fact(3) 发现3不是小于或等于1的，所以Fact(3)调用
  Fact(2)，此函数发现2不是小于等于1的，所以Fact(2)调用
    Fact(1)，此函数发现1是小于观等于1的，所以Fact(1)返回1，从而导致
  Fact(2)返回2x1=2，从而导致
Fact(3)返回3x2=6。
**/
