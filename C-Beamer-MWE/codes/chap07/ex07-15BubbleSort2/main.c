#include <stdio.h>
#include <stdlib.h>

// 函数原型
void Swap(int *, int *);
void InputArray(int [], int);
void OutputArray(int [], int);
int BubbleSortArray(int [], int);

int main()
{
    int a[5] = {5, 3, 7, 9, 2}; // 数组
    int counter; // 循环次数


    //InputArray(a, 5);

    counter = BubbleSortArray(a, 5);

    OutputArray(a, 5);

    printf("Total loop: %d\n", counter);

    return 0;
}

// 函数定义
// 交换两个数
void Swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

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

    // 暂不输出最后一个数
    for(i = 0; i < n - 1; i++)
    {
        printf("%d ", a[i]);
    }

    // 输出最后一个数
    // 避免最后多一个空格
    printf("%d\n", a[i]);
}

// 采用冒泡排序对数组排序
int BubbleSortArray(int a[], int n)
{
    int i = 0, j = 0;
    int counter = 0;

    for(i = 0; i < n - 1; i++ )
    {
        // j<n-1确保数据不越界
        // -i为了减少循环次数
        for(j = 0; j < n - 1 - i; j++)
        {
            if(a[j] > a[j + 1]) // 升序
            {
                Swap(&a[j], &a[j + 1]);
            }
            counter++; //循环计数
        }
    }
    return counter;
}
