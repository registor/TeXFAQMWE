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

int main(void)
{
    struct student *pstd;
    int n, i;

    // 数组大小
    printf("Enter total number of elements: ");
    scanf("%d", &n);

    /*分配内存*/
    pstd = (struct student*)malloc(n * sizeof(struct student));
    if(pstd == NULL)
    {
        printf("Not Enough Memory, Exiting... \n");
        return 0;
    }

    /*使用内存*/
    for(i = 0; i < n; i++)
    {
        scanf("%d", &pstd->id);
        scanf(" "); /* 清理输入缓冲区 */
        gets(pstd->name);
        scanf(" ");
        gets(pstd->gender);
        scanf(" ");
        scanf("%d", &pstd->age);
    }

    printf("\nEntered details are:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d, %s, %s, %d\n",
               pstd->id, pstd->name, pstd->gender, pstd->age);
    }

    // 释放内存
    free(pstd);

    return 0;
}
