#include <stdio.h>
#include <stdlib.h>

#define N 10

//函数原型
// 数组遍历
void Traversal(int *, int, void (*pf)(int *));
// 功能函数
void Input(int *);
void Output(int *);
void Set2Zero(int *);
void PowOdd(int *);

int main()
{
    int iArray[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Traversal(iArray, N, Output);
    printf("\n");
    Traversal(iArray, N, Set2Zero);
    Traversal(iArray, N, Output);
    printf("\n");
    Traversal(iArray, N, Input);
    Traversal(iArray, N, Output);
    printf("\n");
    Traversal(iArray, N, PowOdd);
    Traversal(iArray, N, Output);
    printf("\n");

    return 0;
}
