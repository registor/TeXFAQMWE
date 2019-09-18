#include <stdio.h>
#include <stdlib.h>

#define N 10

//函数原型
// 数组遍历
void Traversal(int *, int, void (*pf)(int *));
// 选择排序（函数指针用于实现比较升/降序）
void SelectionSort(int *, int, int (*)(int, int));
// 功能函数
void Input(int *);
void Output(int *);
// 交换数据
void Swap(int *, int *);
// 比较函数
int Greater(int, int);
int Lesser(int, int);

int main()
{
    int iArray[N];

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    Traversal(iArray, N, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);

    // 升序排序
    SelectionSort(iArray, N, Greater);
    Traversal(iArray, N, Output);
    printf("\n");

    // 降序排序
    SelectionSort(iArray, N, Lesser);
    Traversal(iArray, N, Output);
    printf("\n");

    return 0;
}
