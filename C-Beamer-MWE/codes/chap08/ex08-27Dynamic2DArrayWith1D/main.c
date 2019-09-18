#include <stdio.h>
#include <stdlib.h>

// 函数原型
void SetItem(int *, int, int);
void Display(int *, int, int);

int main(void)
{
    // 声明变量
    int *p = NULL; // 整型指针，初始化为NULL
    int m = 3, n = 4; //数组大小

    /*分配m * n个sizeof(int)字节的
    连续空间存储所有整型数据*/
    p = (int *)malloc(m * n * sizeof(int));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough memory!\n");
        exit(1);
    }

    /* 以指针作为函数实参调用函数 */
    SetItem(p, m, n);
    Display(p, m, n);

   /*释放内存空间*/
    free(p);
    /* 将不用的指针赋值为NULL，防止野指针*/
    p = NULL;

    return 0;
}

// 设置数组元素
void SetItem(int * p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        for(j = 0; j  < n; j++)
        {
            // 用一维的方式模拟二维数组
            *(p + i * n + j) = i * j;
        }
    }
}

// 输出函数
void Display(int * p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        // n-1，不输出最后一个数
        for(j = 0; j  < n - 1; j++)
        {
            // 用一维的方式模拟二维数组
            printf("%d ", *(p + i * n + j));
        }
        // 最后一个数不输出空格
        printf("%d\n", *(p + i * n + j));
    }
}
