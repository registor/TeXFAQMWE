#include <stdio.h>
#include <stdlib.h>

// 函数原型
void SetItem(int **, int, int);
void Display(int **, int, int);

int main(void)
{
    // 声明变量
    int **p = NULL; // 整型指针，初始化为NULL
    int m = 3, n = 4; //数组大小
    int i;//循环变量

    /*先分配m个sizeof(int *)字节的
    连续空间存储每行的首地址*/
    p = (int **)malloc(m * sizeof(int *));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough row's memory!\n");
        exit(1);
    }    
