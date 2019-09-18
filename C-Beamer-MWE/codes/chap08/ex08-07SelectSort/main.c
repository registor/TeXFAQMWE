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

// 函数定义
// 遍历数组
void Traversal(int *pa, int n, void (*pf)(int *))
{
    int *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

// 输入数据
void Input(int * pData)
{
    scanf("%d", pData);
}
// 输出数据
void Output(int * pData)
{
    // 输出
    printf("%d ", *pData);
}

// 交换两个数
void Swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// 比较两个整数
int Greater(int a, int b)
{
    return (a > b) ? 1 : 0;
}

int Lesser(int a, int b)
{
    return (a < b) ? 1 : 0;
}


// 采用选择排序对数组排序
void SelectionSort(int *pa, int n, int (*pf)(int, int))
{
    int i, j;
    int pos = 0; // 选择的位置

    for(i = 0; i < n - 1; i++)
    {
        pos = i; // 每次将pos置为无序数组的起始位置
        for(j = i + 1; j < n; j++) // 遍历无序数组，找到位置
        {
            // 调用传入的比较函数
            if(pf(pa[pos], pa[j]))
            {
                pos = j; // 更新位置
            }
        }
        // 如果不是无序数组的起始位置，则交换
        if(pos != i)
        {
            // 利用指针操作数组
            Swap(pa + i, pa + pos);
        }
    }
}
