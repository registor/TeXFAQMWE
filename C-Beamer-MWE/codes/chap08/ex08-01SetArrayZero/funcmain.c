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

    // 遍历数组
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}
