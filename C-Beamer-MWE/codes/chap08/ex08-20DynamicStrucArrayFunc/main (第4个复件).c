/*动态结构体数组*/
#include <stdio.h>
#include <stdlib.h>

/*结构体声明*/
struct student
{
    int id; /* 学号 */
    char name[20]; /* 姓名 */
    char gender[12]; /* 性别 */
    int age; /* 年龄 */
};

//函数原型
// 数组遍历
void Traversal(struct student *, int, void (*pf)(struct student *));
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

// 函数定义
// 遍历数组
void Traversal(struct student *pa, int n, void (*pf)(struct student *))
{
    struct student *p;

    // 遍历数组，使用指针进行操作
    for(p = pa; p < pa + n; p++)
    {
        pf(p); // 调用传入的函数
    }
}

// 输入数据
void Input(struct student * pData)
{
    scanf("%d", &pData->id);
    scanf(" "); /* 清理输入缓冲区 */
    gets(pData->name);
    scanf(" ");
    gets(pData->gender);
    scanf(" ");
    scanf("%d", &pData->age);
}
// 输出数据
void Output(struct student * pData)
{
    // 输出
    printf("%d, %s, %s, %d\n",
           pData->id, pData->name,
           pData->gender, pData->age);
}
