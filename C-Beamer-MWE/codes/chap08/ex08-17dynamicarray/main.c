/*动态数组*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *pa;
    int n, i, sum = 0;

    // 数组大小
    scanf("%d", &n);

    /*分配内存*/
    pa = (int*)malloc(n * sizeof(int));
    if(pa == NULL)
    {
        printf("Insufficient Memory, Exiting... \n");
        return 0;
    }

    // 输入数组
    for(i = 0; i < n; i++)
    {
        scanf("%d", (pa + i)); // 直接使用指针
        sum = sum + *(pa + i); // 计算和,间接访问元素
    }

    // 输出数组
    for(i = 0; i < n; i++)
    {
        printf("%3d ", *(pa + i));
    }

    // 输出和值
    printf("\nSum of all elements: %d\n", sum);

    // 释放内存
    free(pa);

    return 0;
}
