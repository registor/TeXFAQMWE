#include <stdio.h>
#include <stdlib.h>
...
int main()
{
    int iArray[N];

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    Traversal(iArray, N, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);

    // 升序排序
    QuickSort(iArray, 0, N - 1, Greater);
    Traversal(iArray, N, Output);
    printf("\n");
    //在升序数组中二分查找
    printf("pos = %d\n", BiSearch(iArray, N, 9, Greater));
    // 降序排序
    QuickSort(iArray, 0, N - 1, Lesser);
    Traversal(iArray, N, Output);
    printf("\n");
    //在升序数组中二分查找
    printf("pos = %d\n", BiSearch(iArray, N, 9, Lesser));

    return 0;
}
