/*动态结构体数组*/
#include <stdio.h>
#include <stdlib.h>
...
// 数组遍历
void Traversal(struct student *, int, 
       void (*pf)(struct student *));
// 功能函数
void Input(struct student *);
void Output(struct student *);

int main(void)
{
    struct student *pstd;
    int n;

    // 把输入重定向到文件"data.txt"
    freopen("data.txt", "r", stdin);
    scanf("%d", &n);

    /*分配内存*/
    pstd = (struct student*)malloc(n * sizeof(struct student));
    if(pstd == NULL)
    {
        printf("Not Enough Memory, Exiting... \n");
        return 0;
    }

    Traversal(pstd, n, Input);
    // 把输入重定向回键盘
    freopen("CON", "r", stdin);

    printf("array is:\n");
    Traversal(pstd, n, Output);
    printf("\n");

    // 释放内存
    free(pstd);

    return 0;
}
