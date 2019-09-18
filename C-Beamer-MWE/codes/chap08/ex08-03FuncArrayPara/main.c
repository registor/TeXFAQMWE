#include <stdio.h>
#include <stdbool.h>
#define N 10
//函数原型
int sum(int [], int n); //求数组各元素的和
int main(void)
{    
    int arr[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};// 数组的初始化式
    printf("the sum is %d\n", sum(arr, N));// 函数调用数组名作实参
    return 0;
}
int sum(int a[], int n)//函数头，数组型形参
{
    int sum = 0;    
    for(int i = 0; i < n; i++)// 遍历函数
    {
        sum += a[i];
    }
    return sum;
}
