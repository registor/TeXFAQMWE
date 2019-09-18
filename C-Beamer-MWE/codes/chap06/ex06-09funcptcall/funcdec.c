#include <stdio.h>
#include <stdlib.h>
// 函数原型
int Max(int , int);
int Min(int, int);

//主函数
int main()
{
    /*声明变量并初始化*/
    int a = 10, b = 20;
    int c;

    /*声明函数指针*/
    int (*pf)(int, int);
    pf = Max; /*指向Max函数*/
    c = pf(a, b); /*调用函数*/
    printf("Max=%d\n", c);

