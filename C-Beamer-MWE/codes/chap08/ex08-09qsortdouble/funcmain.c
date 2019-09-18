#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

// 函数原型
// 创建数组
void CreateArray(double *, int n);
// 输出函数
void Output(double *, int);
// 比较函数
int cmp(const void *, const void *);

int main(void)
{
    double dfArray[MAX];

    CreateArray(dfArray, MAX);
    Output(dfArray, MAX);

    printf("\nSorting...\n\n");
    // 调用快速排序函数，注意比较函数指针的使用
    qsort(dfArray, MAX, sizeof(dfArray[0]), cmp);

    Output(dfArray, MAX);
    return(0);
}
