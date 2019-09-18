#include <stdio.h>
#include <stdlib.h>

#define N 10

//函数原型
void InputArray(int [], int);
void OutputArray(int [], int);
void SetArray2Zero(int [], int);

int main()
{
    int iArray[N];

    OutputArray(iArray, N);
    SetArray2Zero(iArray, N);
    OutputArray(iArray, N);
    InputArray(iArray, N);
    OutputArray(iArray, N);

    return 0;
}

// 函数定义
// 为数组输入数据
void InputArray(int a[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}
// 输出数组数据
void OutputArray(int a[], int n)
{
    int i;

    // 遍历数组
    // 暂不输出最后一个数
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", a[i]);
    }

    // 输出最后一个数
    // 避免最后多一个空格
    printf("%d\n", a[i]);
}

// 数组元素清0
void SetArray2Zero(int a[], int n)
{
    int i;

    // 遍历数组
    for(i = 0; i < n; i++)
    {
        a[i] = 0; // 清0
    }
}
