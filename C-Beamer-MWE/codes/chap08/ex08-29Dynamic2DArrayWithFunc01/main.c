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

// 为二维数组开辟空间
int ** AllocArray(int m, int n)
{
    int i;//循环变量
    int **p = NULL;

    /*先分配m个sizeof(int *)字节的
    连续空间存储每行的首地址*/
    p = (int **)malloc(m * sizeof(int *));
    if(NULL == p) // 内存申请失败的处理
    {
        printf("Not enough row's memory!\n");
        exit(1);
    }

    /*再为每一行分配n个sizeof(int)字节
    的连续空间存储每一行的整型数*/
    for (i = 0; i < m; i++)
    {
        p[i] = (int *)malloc(n * sizeof(int));
        if(NULL == p[i]) // 内存申请失败的处理
        {
            printf("Not enough col's memory!\n");
            exit(1);
        }
    }

    // 返回分配的地址
    return p;
}

void DestroyArray(int **p, int m)
{
    int i;
    /*释放每一行的空间*/
    for (i = 0; i < m; i++)
    {
        free(p[i]);
        p[i] = NULL; // 赋值为NULL，防止野指针
    }

    /*释放存储每一行首地址的内存空间*/
    free(p);
}

// 元素赋值
void SetItem(int ** p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        for(j = 0; j  < n; j++)
        {
            // 为数组元素赋值
            p[i][j] = i * j;
        }
    }
}

// 输出函数
void Display(int ** p, int m, int n)
{
    int i, j;//循环变量

    for (i = 0; i < m; i++)
    {
        // n-1，不输出最后一个数
        for(j = 0; j  < n - 1; j++)
        {
            // 遍历数组中每一个元素
            printf("%d ", p[i][j]);
        }
        // 最后一个数不输出空格
        printf("%d\n", p[i][j]);
    }
}
