#include <stdio.h>
#include <stdlib.h>

// 函数原型
void Swap(int *, int *);
void InputArray(int [], int);
void OutputArray(int [], int);
int BubbleSortArray(int [], int);

int main()
{
    int a[5]; // 数组
    int counter; // 循环次数


    InputArray(a, 5);

    counter = BubbleSortArray(a, 5);

    OutputArray(a, 5);

    printf("Total loop: %d\n", counter);

    return 0;
}
