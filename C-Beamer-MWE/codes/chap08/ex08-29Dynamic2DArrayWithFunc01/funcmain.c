#include <stdio.h>
#include <stdlib.h>

// 函数原型
int ** AllocArray(int, int);
void DestroyArray(int **, int);
void SetItem(int **, int, int);
void Display(int **, int, int);

int main(void)
{
    // 声明变量
    int **p = NULL; // 整型指针，初始化为NULL
    int m = 3, n = 4; //数组大小

    // 分配空间，返回二维数组的地址
    p = AllocArray(m, n);

    /* 以二级指针作为函数实参调用函数 */
    SetItem(p, m, n);
    Display(p, m, n);

    // 释放空间
    DestroyArray(p, m);
    // 将不用的指针赋值为NULL，防止野指针
    p = NULL;

    return 0;
}
