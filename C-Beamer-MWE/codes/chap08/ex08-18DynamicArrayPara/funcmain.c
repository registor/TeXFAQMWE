#include <stdio.h>
#include <stdlib.h>

// 数组遍历
void Traversal(int *, int, void (*pf)(int *));
// 功能函数
void Input(int *);
void Output(int *);

int main()
{
    int *pa = NULL;
    int n = 0;

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    // 数组大小
    scanf("%d", &n);
    printf("array length = %d.\n", n);

    /*分配内存*/
    pa = (int*)malloc(n * sizeof(int));
    if(pa == NULL)
    {
        printf("Insufficient Memory, Exiting... \n");
        return 0;
    }

    Traversal(pa, n, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);
    printf("array is:\n");
    Traversal(pa, n, Output);
    printf("\n");

    // 释放内存
    free(pa);
    pa = NULL; //防止悬空指针

    return 0;
}
