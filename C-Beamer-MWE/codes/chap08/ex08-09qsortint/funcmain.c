#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

// 函数原型
// 创建数组
void CreateArray(int *, int n);
// 输出函数
void Output(int *, int);
// 比较函数
int cmp(const void *, const void *);

int main(void)
{
    int iArray[MAX];

    CreateArray(iArray, MAX);
    Output(iArray, MAX);

    printf("\nSorting...\n\n");
    // 调用快速排序函数，注意比较函数指针的使用
    qsort(iArray, MAX, sizeof(iArray[0]), cmp);

    Output(iArray, MAX);
    return(0);
}
